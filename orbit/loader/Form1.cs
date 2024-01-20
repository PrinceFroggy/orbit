#region Declarations
using System;
using System.IO;
using System.Net;
using System.Data;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Threading;
using System.Diagnostics;
using System.Windows.Forms;
using System.ComponentModel;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using Microsoft.Win32;
using loader.Properties;
#endregion

namespace loader
{
    public partial class Form1 : Form
    {
        #region Global Variables
        [DllImport("user32.dll", SetLastError = true)]
        private static extern int FindWindow(string lpClassName, string lpWindowName);

        [DllImport("kernel32")]
        public static extern IntPtr CreateRemoteThread(
          IntPtr hProcess,
          IntPtr lpThreadAttributes,
          uint dwStackSize,
          UIntPtr lpStartAddress,
          IntPtr lpParameter,
          uint dwCreationFlags,
          out IntPtr lpThreadId
        );

        [DllImport("kernel32.dll")]
        public static extern IntPtr OpenProcess(
            UInt32 dwDesiredAccess,
            Int32 bInheritHandle,
            Int32 dwProcessId
            );

        [DllImport("kernel32.dll")]
        public static extern Int32 CloseHandle(
        IntPtr hObject
        );

        [DllImport("kernel32.dll", SetLastError = true, ExactSpelling = true)]
        static extern bool VirtualFreeEx(
            IntPtr hProcess,
            IntPtr lpAddress,
            UIntPtr dwSize,
            uint dwFreeType
            );

        [DllImport("kernel32.dll", CharSet = CharSet.Ansi, ExactSpelling = true)]
        public static extern UIntPtr GetProcAddress(
            IntPtr hModule,
            string procName
            );

        [DllImport("kernel32.dll", SetLastError = true, ExactSpelling = true)]
        static extern IntPtr VirtualAllocEx(
            IntPtr hProcess,
            IntPtr lpAddress,
            uint dwSize,
            uint flAllocationType,
            uint flProtect
            );

        [DllImport("kernel32.dll")]
        static extern bool WriteProcessMemory(
            IntPtr hProcess,
            IntPtr lpBaseAddress,
            string lpBuffer,
            UIntPtr nSize,
            out IntPtr lpNumberOfBytesWritten
        );

        [DllImport("kernel32.dll", CharSet = CharSet.Auto)]
        public static extern IntPtr GetModuleHandle(
            string lpModuleName
            );

        [DllImport("kernel32", SetLastError = true, ExactSpelling = true)]
        internal static extern Int32 WaitForSingleObject(
            IntPtr handle,
            Int32 milliseconds
            );

        string orbitpath = @"C:\ProgramData\orbit.dll";
        string bypasspath = @"C:\ProgramData\bypass.dll";
        #endregion

        #region public void InjectDLL(IntPtr hProcess, string strDLLName)
        public void InjectDLL(IntPtr hProcess, String strDLLName)
        {
            IntPtr bytesout;

            Int32 LenWrite = strDLLName.Length + 1;
            IntPtr AllocMem = (IntPtr)VirtualAllocEx(hProcess, (IntPtr)null, (uint)LenWrite, 0x1000, 0x40);

            WriteProcessMemory(hProcess, AllocMem, strDLLName, (UIntPtr)LenWrite, out bytesout);

            UIntPtr Injector = (UIntPtr)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");

            if (Injector == null)
            {
                return;
            }

            IntPtr hThread = (IntPtr)CreateRemoteThread(hProcess, (IntPtr)null, 0, Injector, AllocMem, 0, out bytesout);

            if (hThread == null)
            {
                return;
            }

            int Result = WaitForSingleObject(hThread, 10 * 1000);

            if (Result == 0x00000080L || Result == 0x00000102L)
            {
                if (hThread != null)
                {
                    CloseHandle(hThread);
                }
                return;
            }

            Thread.Sleep(1000);
            VirtualFreeEx(hProcess, AllocMem, (UIntPtr)0, 0x8000);

            if (hThread != null)
            {
                CloseHandle(hThread);
            }
            timer1.Enabled = false;
            timer2.Enabled = true;
            return;
        }
        #endregion

        #region public Int32 GetProcessId(String proc)
        public Int32 GetProcessId(String proc)
        {
            Process[] ProcList;
            ProcList = Process.GetProcessesByName(proc);
            return ProcList[0].Id;
        }
        #endregion

        #region Form1
        public Form1()
        {
            InitializeComponent();
            try
            {
                byte[] bypassloader = Resources.bypass;
                byte [] orbitloader = Resources.orbit;
                File.WriteAllBytes(bypasspath, bypassloader);
                File.WriteAllBytes(orbitpath, orbitloader);
            }
            catch { }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            if (Properties.Settings.Default.MSLocationbool == true)
            {
                Process.Start(Properties.Settings.Default.MSLocation);
            }
            else
            {
                RegistryKey MSSubKey = Registry.LocalMachine.OpenSubKey("SOFTWARE\\Wizet\\");
                RegistryKey MSRegFolder = MSSubKey.OpenSubKey("MapleStory");

                if (MSRegFolder == null)
                {
                    MessageBox.Show("Can't find the MapleStory location, please launch manually.", "Problem Launching MapleStory", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);

                    this.openFileDialog1.Title = "Find MapleStory...";
                    this.openFileDialog1.FileName = "GameLauncher.exe";
                    this.openFileDialog1.Filter = "Executable | *.exe";

                    if (this.openFileDialog1.ShowDialog() == DialogResult.OK)
                    {
                        Properties.Settings.Default.MSLocation = openFileDialog1.FileName;
                        Properties.Settings.Default.MSLocationbool = true;
                        Properties.Settings.Default.Save();
                    }
                    return;
                }

                string MSLocation = MSRegFolder.GetValue("ExecPath").ToString();

                if (!File.Exists(MSLocation + "\\GameLauncher.exe"))
                {
                    MessageBox.Show("Can't find the MapleStory location, please launch manually.", "Problem Launching MapleStory", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);

                    this.openFileDialog1.Title = "Find Maple...";
                    this.openFileDialog1.FileName = "GameLauncher.exe";
                    this.openFileDialog1.Filter = "Executable | *.exe";

                    if (this.openFileDialog1.ShowDialog() == DialogResult.OK)
                    {
                        Properties.Settings.Default.MSLocation = openFileDialog1.FileName;
                        Properties.Settings.Default.MSLocationbool = true;
                        Properties.Settings.Default.Save();
                    }
                    return;
                }
                Process.Start(MSLocation + "\\GameLauncher.exe");
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (FindWindow("StartUpDlgClass", null) != 0)
            {
                string strProcessName = "MapleStory";

                Int32 ProcID = GetProcessId(strProcessName);

                if (ProcID >= 0)
                {
                    IntPtr hProcess = (IntPtr)OpenProcess(0x1F0FFF, 1, ProcID);
                    if (hProcess == null)
                    {
                        MessageBox.Show("OpenProcess() Failed!");
                        return;
                    }
                    else
                        //InjectDLL(hProcess, bypasspath);
                        InjectDLL(hProcess, orbitpath);
                    this.Visible = false;
                }
            }
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            if (FindWindow(null, "MapleStory") == 0)
            {
                try
                {
                    File.Delete(bypasspath);
                    File.Delete(orbitpath);
                    Environment.Exit(0);
                }
                catch { }
            }
        }
        #endregion
    }
}