#include <room.h>
inherit ROOM;
void create()
{
        set("short", "����");
        set("long", @LONG
һ���������Ƚ���խ��
LONG
  );
  set("exits",([
        "northwest" : __DIR__"huating",
        "southeast" : __DIR__"fangbian",
      ]));  

        set("no_magic",1);
        
        create_door("southeast", "ľ��", "northwest", DOOR_CLOSED);
        setup();
} 
