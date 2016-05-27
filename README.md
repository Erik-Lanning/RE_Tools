# RE_Tools
This is an incredibly basic set of classes to operate on processes.
Currently it support injecting a DLL into a process, or searching a process for a value.

Here are some examples:

// Search the process named "injectorTestExe.exe" for the value 0xDEADBEEF and return the offset.
char needle[sizeof(int) + 1];
int value = 0xDEADBEEF;
snprintf(needle, sizeof(int), "%s", (char*) &value);
needle[sizeof(int)] = '\0';

std::string processName = "injectorTestExe.exe";
scanner testScanner(processName);
std::vector<DWORD> offsets = testScanner.findValue(needle);

// Inject the DLL with path C:\exampleInjectedDll.dll into the process injectorTestExe.exe
std::string processName = "injectorTestExe.exe";
std::string dllPath = "C:\\exampleInjectedDLL.dll";
injector exampleInjector(processName, dllPath);

As you can see these classes make the task incredibly trivial to users.
