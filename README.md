Network Configuration and Dynamic Routing Project
This project demonstrates various network configurations and routing protocols, including OSPF, BGP, and LAN setups using wireless and wired connections. It was designed using Cisco Packet Tracer and involves detailed steps for configuring routers, laptops, and other network devices.

Network Setup
The following devices and configurations are used:

Wireless router (WRT300N) with SSID: ptikta2070.
End devices like laptops with wireless adapters (WPC300N).
Multiple routers (Cisco 2621M) with different IP subnets.
Wireless Router Configuration
Set up the wireless router with the IP address 192.168.5.1 and subnet mask: 255.255.255.0.
Configure WPA2-PSK authentication with Pass Phrase: network2070.
Change the SSID to ptikta2070.
Connecting Two LANs
Two routers were connected using a Serial DCE connection.
Routers were configured with IP address and subnet masks.
Dynamic routing enabled to allow communication between the LANs.
Dynamic Routing
OSPF Configuration
OSPF routing was set up between the routers to dynamically manage and route traffic between different subnets.

BGP Configuration
BGP was configured for autonomous system communication:

Router1 and Router4 in AS100-101.
Connection to AS300 and AS500 with corresponding IP configurations.
Issues Encountered
Problems with configuring BGP due to Cisco Packet Tracer not supporting internal BGP.
Had to modify IP ranges and gateway configurations to work with BGP.
Other issues with subnet masks and RIP configurations were encountered and resolved.
How to Use
Download the project files and open them in Cisco Packet Tracer.
Follow the configuration steps in the document to replicate the setup.
Use the provided commands for configuring routers and enabling communication between LANs.
Credits
Developed by Panagiotis Tiktapanidis as part of a networking course.
