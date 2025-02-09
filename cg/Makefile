MAKE = make

# Target di default
all: build_engine build_engineTest build_client

# Compilazione dell'engine
build_engine:
	$(MAKE) -C engine all

# Compilazione di engineTest, che dipende da build_engine
build_engineTest: build_engine
	$(MAKE) -C engineTest all

# Compilazione del client, che dipende da build_engine
build_client: build_engine
	$(MAKE) -C client all

# Pulizia dei vari componenti
clean: clean_engine clean_engineTest clean_client

# Pulizia dell'engine
clean_engine:
	$(MAKE) -C engine clean

# Pulizia dei test dell'engine
clean_engineTest:
	$(MAKE) -C engineTest clean

# Pulizia del client
clean_client:
	$(MAKE) -C client clean

# Dichiarazione delle regole come "phony" (ovvero non file)
.PHONY: all clean build_engine build_engineTest build_client clean_engine clean_engineTest clean_client