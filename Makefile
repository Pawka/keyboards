HOME=$(shell pwd)
QMK_HOME=$(HOME)/qmk_firmware
QMK_REPO=https://github.com/qmk/qmk_firmware
VENV=$(HOME)/env

KYRIA=keyboards/splitkb/kyria/keymaps/pawka
KYRIA_LINK=$(QMK_HOME)/$(KYRIA)

ERGODOX=keyboards/ergodox_ez/keymaps/pawka
ERGODOX_LINK=$(QMK_HOME)/$(ERGODOX)

.PHONY: all
all: $(VENV) symlinks

.PHONY: symlinks
symlinks: $(KYRIA_LINK) $(ERGODOX_LINK)

.PHONY: submodules
submodules: $(QMK_HOME)
	@echo "Update git sub-modules..."
	git submodule sync --recursive
	git submodule update --init --recursive --progress --remote

$(QMK_HOME):
	@echo "Add git sub-modules..."
	git submodule add -f $(QMK_REPO)

$(VENV): submodules
	virtualenv $(VENV)
	$(VENV)/bin/python -m pip install qmk -r $(QMK_HOME)/requirements.txt

$(KYRIA_LINK): submodules
	@echo "Symklink for Kyria"
	ln -Tsf $(HOME)/$(KYRIA) $(KYRIA_LINK)

$(ERGODOX_LINK): submodules
	@echo "Symklink for Ergodox"
	ln -Tsf $(HOME)/$(ERGODOX) $(ERGODOX_LINK)

.PHONY: clean
clean:
	rm -rf $(KYRIA_LINK) $(ERGODOX_LINK)
