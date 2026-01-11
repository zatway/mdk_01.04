using System.Runtime.InteropServices;

class Program
{
    [DllImport("kernel32.dll", SetLastError = true)]
    static extern IntPtr VirtualAlloc(IntPtr lpAddress, UIntPtr dwSize, uint flAllocationType, uint flProtect);

    [DllImport("kernel32.dll", SetLastError = true)]
    [return: MarshalAs(UnmanagedType.Bool)]
    static extern bool VirtualFree(IntPtr lpAddress, UIntPtr dwSize, uint dwFreeType);

    [DllImport("kernel32.dll")]
    static extern void ZeroMemory(IntPtr ptr, UIntPtr numBytes);

    [DllImport("kernel32.dll")]
    static extern void FillMemory(IntPtr ptr, UIntPtr numBytes, byte fill);

    [DllImport("kernel32.dll")]
    static extern void GetSystemInfo(ref SYSTEM_INFO lpSystemInfo);

    [StructLayout(LayoutKind.Sequential)]
    struct SYSTEM_INFO
    {
        public ushort wProcessorArchitecture;
        public ushort wReserved;
        public uint dwPageSize;
        public UIntPtr lpMinimumApplicationAddress;
        public UIntPtr lpMaximumApplicationAddress;
        public UIntPtr dwActiveProcessorMask;
        public uint dwNumberOfProcessors;
        public uint dwProcessorType;
        public uint dwAllocationGranularity;
        public ushort wProcessorLevel;
        public ushort wProcessorRevision;
    }

    const uint MEM_COMMIT = 0x1000;
    const uint MEM_RESERVE = 0x2000;
    const uint MEM_RELEASE = 0x8000;
    const uint PAGE_READWRITE = 0x04;

    static void Main(string[] args)
    {
        Console.OutputEncoding = System.Text.Encoding.UTF8;
        
        SYSTEM_INFO si = new SYSTEM_INFO();
        GetSystemInfo(ref si);
        uint pageSize = si.dwPageSize;
        uint granularity = si.dwAllocationGranularity;

        Console.WriteLine($"Размер страницы: {pageSize} байт");
        Console.WriteLine($"Гранулярность выделения памяти: {granularity} байт\n");

        UIntPtr regionSize = (UIntPtr)(2 * pageSize);

        IntPtr region1 = VirtualAlloc(IntPtr.Zero, regionSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
        if (region1 == IntPtr.Zero)
        {
            Console.WriteLine($"Ошибка резервирования региона 1: {Marshal.GetLastWin32Error()}");
            return;
        }

        IntPtr region2 = VirtualAlloc(IntPtr.Zero, regionSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
        if (region2 == IntPtr.Zero)
        {
            Console.WriteLine($"Ошибка резервирования региона 2: {Marshal.GetLastWin32Error()}");
            VirtualFree(region1, UIntPtr.Zero, MEM_RELEASE);
            return;
        }

        Console.WriteLine($"Регион 1 зарезервирован по адресу: 0x{region1.ToInt64():X16}");
        Console.WriteLine($"Регион 2 зарезервирован по адресу: 0x{region2.ToInt64():X16}\n");

        Console.WriteLine("Обнуление региона 1 (ZeroMemory)...");
        ZeroMemory(region1, regionSize);

        Console.Write("Введите число от 0 до 127 для региона 2: ");
        if (!byte.TryParse(Console.ReadLine(), out byte fillValue) || fillValue > 127)
        {
            Console.WriteLine("Некорректное значение! Используется 42 по умолчанию.");
            fillValue = 42;
        }

        Console.WriteLine($"Заполнение региона 2 значением {fillValue} (FillMemory)...");
        FillMemory(region2, regionSize, fillValue);

        Console.WriteLine("\nПервые 16 байт региона 1 (должны быть 0x00):");
        PrintBytes(region1, 16);

        Console.WriteLine($"\nПервые 16 байт региона 2 (должны быть 0x{fillValue:X2}):");
        PrintBytes(region2, 16);

        // Освобождаем память
        VirtualFree(region1, UIntPtr.Zero, MEM_RELEASE);
        VirtualFree(region2, UIntPtr.Zero, MEM_RELEASE);

        Console.WriteLine("\nРегионы освобождены. Нажмите любую клавишу для выхода...");
        Console.ReadKey();
    }

    static unsafe void PrintBytes(IntPtr ptr, int count)
    {
        byte* p = (byte*)ptr.ToPointer();
        for (int i = 0; i < count; i++)
        {
            Console.Write($"{p[i]:X2} ");
            if ((i + 1) % 8 == 0) Console.Write("  ");
        }

        Console.WriteLine();
    }
}