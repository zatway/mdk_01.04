using System.Runtime.InteropServices;

class Program
{
    [DllImport("kernel32.dll")]
    static extern uint GetCurrentProcessId();

    [DllImport("kernel32.dll")]
    static extern IntPtr GetCurrentProcess();

    [DllImport("kernel32.dll", SetLastError = true)]
    static extern bool DuplicateHandle(
        IntPtr hSourceProcessHandle,
        IntPtr hSourceHandle,
        IntPtr hTargetProcessHandle,
        out IntPtr lpTargetHandle,
        uint dwDesiredAccess,
        bool bInheritHandle,
        uint dwOptions
    );

    [DllImport("kernel32.dll", SetLastError = true)]
    static extern IntPtr OpenProcess(
        uint dwDesiredAccess,
        bool bInheritHandle,
        uint dwProcessId
    );

    [DllImport("kernel32.dll", SetLastError = true)]
    static extern bool CloseHandle(IntPtr hObject);

    const uint PROCESS_ALL_ACCESS = 0x001F0FFF;
    const uint DUPLICATE_SAME_ACCESS = 0x00000002;

    static void Main()
    {
        uint processId = GetCurrentProcessId();
        Console.WriteLine($"ID процесса: {processId}");

        IntPtr pseudoHandle = GetCurrentProcess();
        Console.WriteLine($"Псевдодескриптор: {pseudoHandle}");

        bool duplicated = DuplicateHandle(
            pseudoHandle,
            pseudoHandle,
            pseudoHandle,
            out IntPtr dupHandle,
            0,
            false,
            DUPLICATE_SAME_ACCESS
        );

        if (!duplicated)
        {
            Console.WriteLine("Ошибка DuplicateHandle");
            return;
        }

        Console.WriteLine($"Дескриптор (DuplicateHandle): {dupHandle}");

        IntPtr openHandle = OpenProcess(PROCESS_ALL_ACCESS, false, processId);
        Console.WriteLine($"Дескриптор (OpenProcess): {openHandle}");

        CloseHandle(openHandle);
        Console.WriteLine($"Закрыт дескриптор OpenProcess: {openHandle}");

        CloseHandle(dupHandle);
        Console.WriteLine($"Закрыт дескриптор DuplicateHandle: {dupHandle}");

        Console.ReadKey();
    }
}
