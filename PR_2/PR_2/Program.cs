using System.Text;
using System.Runtime.InteropServices;
using Microsoft.Win32;

namespace PR_2
{
    class Program
    {
        [DllImport("kernel32.dll", CharSet = CharSet.Unicode)]
        static extern bool GetComputerName(StringBuilder lpBuffer, ref int nSize);

        [DllImport("kernel32.dll", CharSet = CharSet.Auto)]
        static extern uint GetWindowsDirectory(StringBuilder lpBuffer, uint uSize);

        [DllImport("kernel32.dll", CharSet = CharSet.Auto)]
        static extern uint GetSystemDirectory(StringBuilder lpBuffer, uint uSize);

        [DllImport("kernel32.dll", CharSet = CharSet.Auto)]
        static extern uint GetTempPath(uint nBufferLength, StringBuilder lpBuffer);

        [DllImport("kernel32.dll")]
        static extern uint GetVersion();

        static void Main(string[] args)
        {
            Console.OutputEncoding = Encoding.UTF8;

            StringBuilder name = new StringBuilder(256);
            int size = name.Capacity;
            if (GetComputerName(name, ref size))
            {
                Console.WriteLine($"Имя компьютера: {name}");
            }

            StringBuilder path = new StringBuilder(260);

            GetWindowsDirectory(path, (uint)path.Capacity);
            Console.WriteLine($"Каталог Windows: {path}");

            path.Clear();
            GetSystemDirectory(path, (uint)path.Capacity);
            Console.WriteLine($"Системный каталог: {path}");

            path.Clear();
            GetTempPath((uint)path.Capacity, path);
            Console.WriteLine($"Каталог временных файлов: {path}");

            uint version = GetVersion();
            uint major = version & 0xFF;
            uint minor = (version >> 8) & 0xFF;
            uint build = (version >> 16) & 0xFFFF;

            Console.WriteLine($"Версия ОС (GetVersion): {major}.{minor} (сборка {build})");

            Console.WriteLine($"Версия ОС (Environment): {Environment.OSVersion.Version}");
            string productName = Registry.GetValue(
                @"HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion",
                "ProductName", "")?.ToString() ?? "Неизвестно";
            Console.WriteLine($"Полное имя ОС: {productName}");
        }
    }
}