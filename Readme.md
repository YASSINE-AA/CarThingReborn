# Template PlatformIO
This repo is a template project, for using ESP32 with platformIO.
I use platform IO CLI. 

```bash
curl -fsSL -o get-platformio.py https://raw.githubusercontent.com/platformio/platformio-core-installer/master/get-platformio.py
python3 get-platformio.py
```
then run the script 

```bash
cd /path-to-dir/where/get-platformio.py/is-located

# run it
python get-platformio.py

```
> NOTE <br> 
> for more INFO visit the [plaftromIO](https://docs.platformio.org/en/latest/core/installation/methods/installer-script.html) website

By manipulating `platformio.ini`, you can set it to your needs. 

I have also provided a makefile for ease of use. 

Provided targets are: 

- `build` : to build project 
- `flash` to upload code to esp32 
- `generate_commands_json`: for intelicence in vim 
- `init_project`: initialises the project 