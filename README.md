# Open Ephys Open IGT Link

This repository contains a library for the [Open Ephys GUI](https://github.com/open-ephys/plugin-GUI) to send messages via [Open IGT LINK](http://openigtlink.org/). 

The library is currently used by [OpenEphysLeadOR](https://github.com/netstim/OpenEphysLeadOR).

## Installation

- Manual

The compiled dlls for GUI v6 is available from the Releases page. They should be downloaded and placed under `C:\ProgramData\Open Ephys\shared-api8`.

- Github CLI

Using Github CLI is easy to stay up to date with latest release using the following command:

```PowerShell
gh release download --clobber --dir "C:\ProgramData\Open Ephys\shared-api8" --pattern *.dll --repo netstim/OpenEphysIGTLink
```

- From Source

Alternativly, one can also compile this plugin from source. See Open Ephys GUI Documentation for instructions.

- From the GUI

The plugin is currently not available from the GUI Plugin installer. Use one of the avobe methods.