// edited by mind
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "Ͳ��");
        set("long", @LONG
��������һƬ�ڰ���������վ��һ��Ͳ���һ������
���»��Ͳ�ӡ�
LONG
  );
  set("exits",([
        "up" : __DIR__"tongzi1",
        "east" : __DIR__"didao1",
        
      ]));  
        set("no_magic",1);
        
        setup();
} 
