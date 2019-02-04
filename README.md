# ThreadedQtEtaNetServer
C++/Qt 5.8 - Threaded Server that gets Messages and writes into SQLite DB 

# Threaded ηNet Server - Networking of Cyber-Physical Objects (OPS) to Managing Energy Systems

## Context of the development
In the context of the ηNet energy management project a system was developed that allows the energetic analysis and the management of control of energy systems.The energy systems of the future will be a network of a multitude of technologies and applications. However, the diversity of these components, their topology and the size of the systems lead to a high degree of complexity. The energy systems of the future are confronted with serious problems for system stability and efficiency. The aim of the project is to develop a software and network system that abstracts and digitizes energy and information flows. This abstraction and digitization enables cross-system control.


## Concept of Energy Management System
The aim is to establish a management layer that has an influence on the control of the energy system. In this way, higher adaptation strategies can be implemented.

<img src="LayerOfSbstraction.png" width=35%>

Figure1: Layered representation of the abstraction. 

For digitization, all field elements of the energy system are classified into three classes: producers, consumers and storages. Each real element is understood as a cyber-physical object (CPO) of these classes. This CPOs carry all values to fully describe and control the field elements of the energy system and serve as an interface for external applications. The real CPOs are generated by a single on-board computer on which the client software for the ηNet network also runs. Together with the ηNet-servers, it is possible to easily create a network with CPOs to collect all data and control the entire plant together with a database. Due to the CPOs, the management system knows all about existing system components and the networking. This knowledge base is used for plant-specific optimization or adaptation algorithms. For example, to minimize costs or CO2 emissions. This enables higher control strategies and data managed systems. 

<img src="etaNetSystemArchitecture.png" width=70%>

Figure2: Schematic representation of the system architecture concept. Producer (P), Consumer (C), Storage (S), Data Acquisition (DQ), Controlling and Configuration (Conig). The big blue arrows indicate the direction of the energy flows.

<img src="etanetSchematicSystem.png" width=70%>

Figure3: Schematic representation of the system workflow. 

## Prerequisites
* To use the software, NI LabVIEW version 2017 or later is required. LabVIEW is a development environment and is for any measurement or control system. If you don't have a license for the development environment, you can use the evaluating version for now. [You can download it here](http://www.ni.com/de-de/shop/labview.html). 
* SQLite is used here for the database. The SQLite library can be integrated directly into corresponding applications so that no additional server software is required. Here the SQLite library for LabVIEW by Dr. James Powell was used. [Here you can download and install it](http://sine.ni.com/nips/cds/view/p/lang/de/nid/212894). 


## Deployment and Starting Demo Energy System
If so far everything is installed, then open a terminal and clone this repro:

```
cd ~
git clone https://github.com/IKKUengine/SimulatedCPSLabVIEWEnergySystem.git
cd SimulatedCPSLabVIEWEnergySystem
```

or download [it](https://github.com/IKKUengine/SimulatedCPSLabVIEWEnergySystem/archive/master.zip) to your home directory and open the folder. 

Look for a file with the extension .lvproj and double-click it. 
Only the two VIs are relevant for the start of the demo energy system:
* Virtual-TimeSimulated_EnergySystem.vi
* EnergyMonitoring.vi

Start first Virtual-TimeSimulated_EnergySystem.vi and then EnergyMonitoring.vi. 
The system is programmed so that the corresponding database and its structure is created automatically at startup. An insight into the database allows the EnergyMonitoring.vi. You can also use the [DB Browser for SQLite](https://sqlitebrowser.org/).

## OOP-oriented Programming Paradigm of the Management
The control interface of the CPOs is summarized as a table (control matrix) in the database. If one of the parameters changes, this has a direct influence on the CPOs and therefore on the system itself.  

For example, self-organizing algorithms can use this control matrix:
* If a producer fails, another inactive producer can be switched on or energy consumers can be deactivated.  
* In order to save costs, low-cost producers can be prioritized higher.
* to save carbon dioxide, emission-free producers can be prisorized higher.
* etc.  

**Management Interface**

Start EnergyControlling.vi. On the surface of EnergyControlling.vi you can directly change the management parameters in the table and look at the result in Virtual-TimeSimulated_EnergySystem.vi and EnergyMonitoring.vi. Just try it out. In Folder \SimulatedCPSLabVIEWEnergySystem\management there are some Demo-VIs but with no content yet. Currently the demo versions of management algorithms are under development and will follow soon...

## System and Software Engineer, Project Supervisor and Author
Ferhat Aslan
## Project Collaboration and Software Engineer
Furqan Abbasi

## License
This project is licensed under MIT - see the [LICENSE](LICENSE.md) file for details


