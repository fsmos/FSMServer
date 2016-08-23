.PHONY: clean All

All:
	@echo "----------Building project:[ fsmmn825 - Release ]----------"
	@cd "fsmmn825" && "$(MAKE)" -f  "fsmmn825.mk"
clean:
	@echo "----------Cleaning project:[ fsmmn825 - Release ]----------"
	@cd "fsmmn825" && "$(MAKE)" -f  "fsmmn825.mk" clean
