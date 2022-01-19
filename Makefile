HOME=$(shell pwd)
QMK_HOME=$(HOME)/qmk_firmware
QMK_REPO=https://github.com/qmk/qmk_firmware

KYRIA=keyboards/splitkb/kyria/keymaps/pawka
KYRIA_LINK=$(QMK_HOME)/$(KYRIA)

ERGODOX=keyboards/ergodox_ez/keymaps/pawka
ERGODOX_LINK=$(QMK_HOME)/$(ERGODOX)

.PHONY: all
all: $(QMK_HOME) $(KYRIA_LINK) $(ERGODOX_LINK)
	@echo "Update git sub-modules..."
	git submodule sync --recursive
	git submodule update --init --recursive --progress

$(QMK_HOME):
	@echo "Add git sub-modules..."
	git submodule add -f $(QMK_REPO)

$(KYRIA_LINK):
	@echo "Symklink for Kyria"
	ln -s $(HOME)/$(KYRIA) $(KYRIA_LINK)

$(ERGODOX_LINK):
	@echo "Symklink for Ergodox"
	ln -s $(HOME)/$(ERGODOX) $(ERGODOX_LINK)

.PHONY: clean
clean:
	rm -rf $(KYRIA_LINK) $(ERGODOX_LINK)
