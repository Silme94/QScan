# QScan
Windows port scanner like nmap.

# Manual 
```
QScan - User Manual
[https://github.com/Silme94/QScan]

Description:
QScan is a command-line tool that allows you to scan the ports of a specified IP address to determine which ports are open and available for communication.

Usage:
QScan i- <IP>

Options:
 -i <IP>           The IP address of the target to scan. REQUIRED.
 -p <PORT>         Scan only one specified port and return if the port is open or not.
 -m <MAX_RANGE>    Set the max range ports to scan. Cannot be used with '-p' flag. DEFAULT : 65535. RECOMMANDED : 10000
 -t <THREAD>       Set thread numbers. DEFAULT : 10

Usage Examples:
  QScan -i 192.168.0.1   Scan the ports of the IP address 192.168.0.1.

Tips:
- Use the IP address of a remote machine that you have permission to scan.
- The scan results indicate open ports but do not provide information about the services that may be running on those ports.
- Make sure you have the necessary privileges to perform a port scan.

Disclaimer:
Misusing this scanner to attempt unauthorized access to systems or networks is strictly prohibited. Be sure to use this tool ethically and responsibly, adhering to all applicable laws and regulations.

Author:
[https://github.com/Silme94]
```
