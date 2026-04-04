# FbQe

Firebird SQL UDR plugin for Windows.

[![MSBuild](https://github.com/dant02/FbQe/actions/workflows/msbuild.yml/badge.svg)](https://github.com/dant02/FbQe/actions/workflows/msbuild.yml)

## What this project is

FbQe builds a native DLL plugin for [Firebird SQL](https://www.firebirdsql.org) using the Firebird UDR (User Defined Routine) API.

The plugin is intended to be copied into Firebird's `plugins\\udr` folder and then registered in the database with SQL statements.

## Current functions

### GetCurrentTimestampUTC

Returns the current date and time in UTC as a Firebird `TIMESTAMP`.

Declaration:

```sql
CREATE FUNCTION GetCurrentTimestampUTC()
RETURNS TIMESTAMP
EXTERNAL NAME 'FbQe!GetCurrentTimestampUTC'
ENGINE UDR;
```

Example usage:

```sql
SELECT GetCurrentTimestampUTC()
FROM RDB$DATABASE;
```

## Repository layout

- `FbQe/` - native Visual Studio C++ project that builds the plugin DLL
- `FbQe.Tests/` - MSTest project for automated tests
- `.github/workflows/` - CI build workflow
- `declare_functions.sql` - SQL script to register plugin functions in Firebird
- `checkout.bat` - helper script to clone Firebird source headers into `.fb`
- `update.bat` - helper script to copy build outputs into a local Firebird installation

## Prerequisites

To build and use this project locally, you will typically need:

- Windows
- Firebird SQL installed locally
- Visual Studio 2022 or later with C++ desktop build tools
- .NET 8 SDK for the test project
- Access to Git to clone the Firebird source headers used by the C++ project

The repository pins the .NET SDK version in `global.json`. At the time of writing, the pinned SDK is `8.0.419`.

## Build setup

The native project includes Firebird header files from a local `.fb` folder.

To create that folder, run:

```bat
checkout.bat
```

This clones the Firebird source tree into `.fb`, which is used by `FbQe/FbQe.vcxproj`.

## Build

You can build the project in Visual Studio by opening:

```text
FbQe.slnx
```

Or build from the command line with MSBuild:

```bat
msbuild /m /p:Configuration=Release /p:Platform=x64 .
```

The GitHub Actions workflow builds the `Release|x64` configuration only. The command above matches the CI build configuration.

The CI workflow installs the same pinned .NET SDK version before restore and build to keep local and CI behavior consistent.

Typical release outputs are created under:

```text
x64\Release\
```

Important files for deployment:

- `FbQe.dll`
- `Ijwhost.dll`
- `FbQe.runtimeconfig.json`

## Deployment

1. Build the project in `Release` configuration.
2. Copy the release output files into the `plugins\udr` folder inside your Firebird installation directory.
3. Run the SQL statements from `declare_functions.sql` against your Firebird database.

The helper script below can be used on a local machine where Firebird is installed in `c:\fb`:

```bat
update.bat release
```

That script:

- stops and restarts the `FirebirdServerDefaultInstance` service
- copies the release build artifacts into `c:\fb\plugins\udr`

## Registering the function

The repository includes an example registration script:

```sql
-- Firebird 5.0.3
CREATE FUNCTION GetCurrentTimestampUTC()
RETURNS TIMESTAMP
EXTERNAL NAME 'FbQe!GetCurrentTimestampUTC'
ENGINE UDR;
```

See:

- `declare_functions.sql`

## Development notes

- The plugin writes log output to `c:\fb\fbqe.log`
- The project currently appears to be focused on Windows deployment
- The test project exists, but automated coverage is still minimal

## Continuous integration

GitHub Actions builds the project on Windows using the workflow in `.github/workflows/msbuild.yml`.

The workflow explicitly installs .NET SDK `8.0.419` to avoid unexpected runner changes affecting the `net8.0` test project.
It currently validates `Release|x64` only and uploads artifacts from `x64\Release\`.
Debug builds are intended for local development and are not validated by CI.

## License

See `LICENSE`.
