# Metafetch

A simple tool to edit metadata and hexdump files.

## Installation
**TODO**

## Usage

`-F / --file`: Path to the file to fetch metadata from.  
`-d / --hexdump`: Flag for Hexdump.  
`-f / --fetch-metadata`: Flag for fetching metadata.  
`-e / --edit-metadata`: Flag for editing metadata.  
`-o / --output`: Output path (if not provided will print on terminal).  
`-V / --version`: Show the version of the tool.  
`-h / --help`: Show this help message.  

## Examples

Hexdumping a file and outputting to a file:  
```bash
./metafetch -F /bin/somebinarie.o -d -o /tmp/hexdump.txt
```

Fetching metadata from an image and not using the output flag:  
```bash
./metafetch --file /img/funnycat.png --fetch-metadata
```