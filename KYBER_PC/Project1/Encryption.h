#pragma once

#include <stdio.h>

#include "RandomBytes.h"
#include "Params.h"

void GetNewOriginText(uint8_t *ct,
					  uint8_t *ot,
					  const uint8_t pk[SECRET_KEY_SIZE]);