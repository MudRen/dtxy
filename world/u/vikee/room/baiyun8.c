inherit ROOM;
#include <room.h>

void create ()
{
  set ("short", "���ƶ�");
  set ("long", @LONG

������С������ȴ������ء�
LONG);
  set("exits", ([ /* sizeof() == 3 */
  "northwest" : __DIR__"baiyun9",
  "northeast" : __DIR__"baiyun10",
  "north":      __DIR__"baiyun11",
]));

  set("no_clean_up", 1);
  setup();
}
int clean_up()
{
      return 0;
}

