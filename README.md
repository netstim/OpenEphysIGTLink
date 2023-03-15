# Open Ephys Open IGT Link

This repository contains a library for the [Open Ephys GUI](https://github.com/open-ephys/plugin-GUI) to send messages via [Open IGT LINK](http://openigtlink.org/). 

The library is currently used by [OpenEphysLeadOR](https://github.com/netstim/OpenEphysLeadOR).

## Installation

### **Windows**

#### _Manual_

The compiled dlls for GUI v6 is available from the Releases page. They should be downloaded and placed under `C:\ProgramData\Open Ephys\shared-api8`.

#### _Github CLI_

Using Github CLI is easy to stay up to date with latest release using the following command:

```PowerShell
gh release download --clobber --dir "C:\ProgramData\Open Ephys\shared-api8" --pattern *.dll --repo netstim/OpenEphysIGTLink
```

#### _From Source_

Alternativly, one can also compile this plugin from source. See [Open Ephys GUI Documentation](https://open-ephys.github.io/gui-docs/Developer-Guide/Compiling-plugins.html) for instructions.

#### _From the GUI_

The plugin is currently not available from the GUI Plugin installer. Use one of the avobe methods.

### **MacOS**

#### _Manual_

The compiled dylib for GUI v6 is available from the Releases page. They should be downloaded and placed under `~/Library/Application Support/open-ephys/shared-api8`.

#### _Github CLI_

Using Github CLI is easy to stay up to date with latest release using the following command:

```sh
gh release download --clobber --dir ~/Library/Application\ Support/open-ephys/shared-api8 --pattern *.dylib --repo netstim/OpenEphysIGTLink
```

#### _From Source_

Alternativly, one can also compile this plugin from source. See [Open Ephys GUI Documentation](https://open-ephys.github.io/gui-docs/Developer-Guide/Compiling-plugins.html) for instructions.

#### _From the GUI_

The plugin is currently not available from the GUI Plugin installer. Use one of the avobe methods.