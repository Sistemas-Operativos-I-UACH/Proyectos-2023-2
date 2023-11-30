obj-m += buenosdias.o

all:
	echo "Compilando modulo Kernel WIFI UACH"
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
