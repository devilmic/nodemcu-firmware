// Module for interfacing with the DHTxx sensors (xx = 11-21-22-33-44).

#include "lualib.h"
#include "lauxlib.h"
#include "auxmods.h"
#include "lrotable.h"
#include "cpu_esp8266.h"
#include "ir.h"
#include "irint.h"

#define NUM_DHT GPIO_PIN_NUM

// ****************************************************************************
// DHT functions
int platform_ir_exists( unsigned id )
{
  return ((id < NUM_DHT) && (id > 0));
}

// Lua: status, temp, humi, tempdec, humidec = dht.read11( id ))
static int ir_lapi_readir( lua_State *L )
{
  unsigned id = luaL_checkinteger( L, 1 );
  MOD_CHECK_ID( ir, id );
/*
  lua_pushinteger( L, dht_read11(id) );
  double temp = dht_getTemperature();
  double humi = dht_getHumidity();
  int tempdec = (int)((temp - (int)temp) * 1000);
  int humidec = (int)((humi - (int)humi) * 1000);
  lua_pushnumber( L, temp );
  lua_pushnumber( L, humi );
  lua_pushnumber( L, tempdec );
  lua_pushnumber( L, humidec );
  return 5;
*/
  return 0;
}

// Lua: status, temp, humi, tempdec, humidec = dht.readxx( id ))
static int ir_lapi_sendir( lua_State *L )
{
  unsigned id = luaL_checkinteger( L, 1 );
  MOD_CHECK_ID( ir, id );
/*  lua_pushinteger( L, dht_read(id) );
  double temp = dht_getTemperature();
  double humi = dht_getHumidity();
  int tempdec = (int)((temp - (int)temp) * 1000);
  int humidec = (int)((humi - (int)humi) * 1000);
  lua_pushnumber( L, temp );
  lua_pushnumber( L, humi );
  lua_pushnumber( L, tempdec );
  lua_pushnumber( L, humidec );
  return 5;
*/
  return 0;
}


// Module function map
#define MIN_OPT_LEVEL   2
#include "lrodefs.h"
const LUA_REG_TYPE ir_map[] =
{
  { LSTRKEY( "readir" ),  LFUNCVAL( ir_lapi_readir ) },
  { LSTRKEY( "sendir" ), LFUNCVAL( ir_lapi_sendir ) },
#if LUA_OPTIMIZE_MEMORY > 0
  { LSTRKEY( "OK" ), LNUMVAL( IRLIB_OK ) },
  { LSTRKEY( "ERROR_CHECKSUM" ), LNUMVAL( IRLIB_ERROR_CHECKSUM ) },
  { LSTRKEY( "ERROR_TIMEOUT" ), LNUMVAL( IRLIB_ERROR_TIMEOUT ) },
#endif
  { LNILKEY, LNILVAL }
};

LUALIB_API int luaopen_ir( lua_State *L )
{
#if LUA_OPTIMIZE_MEMORY > 0
  return 0;
#else // #if LUA_OPTIMIZE_MEMORY > 0
  luaL_register( L, AUXLIB_IR, ir_map );

  // Add the constants

  return 1;
#endif // #if LUA_OPTIMIZE_MEMORY > 0
}
