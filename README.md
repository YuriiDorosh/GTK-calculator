# GTK Calculator

## How to run the app:

### The first way:

#### Cloning the repository

--> Clone the repository using the command below :

```bash
git clone https://github.com/YuriiDorosh/GTK-calculator.git
```
--> Move into the directory where we have the project files :

```bash
cd GTK-calculator 
```
--> Install the requirements :

```bash
sudo apt update
sudo apt install gcc
sudo apt install pkg-config
sudo apt-get install libgtk-3-dev
```
--> Project launch :

```bash
gcc calculator.c -o calc `pkg-config --cflags --libs gtk+-3.0`
./calc
```

### The second way:

#### Cloning the repository

--> Clone the repository using the command below :

```bash
git clone https://github.com/YuriiDorosh/GTK-calculator.git
```

--> Move into the directory where we have the project files :

```bash
cd GTK-calculator 
```

--> Use launching file:

```bash
chmod +x run.sh
./build_and_run.sh
```

