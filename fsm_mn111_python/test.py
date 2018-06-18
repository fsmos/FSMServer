#!/usr/bin/env python3

import fsmgetmn111
import json

print(json.loads(fsmgetmn111.fsm_mn111_start_autoscan()));
print(json.loads(fsmgetmn111.fsm_mn111_get_voltage()));
