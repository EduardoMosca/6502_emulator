# 6502 processor emulator

This project intends to create a 6502 processor emulator for the porpose of learning the concepts processors work, to train the C programming language skills so as CMake and unit tests.

The project was based on the fllowing tutorial:
[Emulating a CPU in C++ (6502)](https://www.youtube.com/watch?v=qJgsuQoy9bc)

Which has its own repository on github:
[Github](https://github.com/davepoo/6502Emulator)

And as complement of the development the following website:
[6502](http://www.6502.org/users/obelisk/)

## Usage

### First clone the project

```bash
git clone https://github.com/EduardoMosca/6502_emulator.git
git submodule update --init --recursive
```

### Set the CMake environment

```bash
mkdir build
cd build
cmake ..
```

### Run the application

```bash
cmake --build .
```

Once the project finish the building it is possible it will generate 2 executables one for the tests and another to the main program

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License

[MIT](https://choosealicense.com/licenses/mit/)
