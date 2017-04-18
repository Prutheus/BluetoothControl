CFLAGS	= -I/opt/local/include --std=c99 `pkg-config appindicator3-0.1 --cflags`
LDFLAGS	= -L/opt/local/lib -lm `pkg-config appindicator3-0.1 --libs`

all: BluetoothControl

BluetoothControl: BluetoothControl.c