// edited by mind
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "�ص�");
        set("long", @LONG
�����ǵ�̾��µ�ʯ�ڣ�����Ƕ�ŷ�����ͭ�ơ�
LONG
  );
  set("exits",([
        "west" : __DIR__"tongzi4",
        "east" : __DIR__"didaotou",
      ]));  
        set("no_magic",1);
        
        setup();
} 
