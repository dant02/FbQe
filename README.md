# FbQe

Firebird SQL plugin, https://www.firebirdsql.org

[![MSBuild](https://github.com/dant02/FbQe/actions/workflows/msbuild.yml/badge.svg)](https://github.com/dant02/FbQe/actions/workflows/msbuild.yml)

## Contents of the plugin

### Functions

GetCurrentTimestampUTC - returns timestamp of current date and time in UTC

## Deployment steps

- Copy contents of release package to folder \plugins\udr located in the installation folder of Firebird SQL
- Execute statements in declare_functions.sql
