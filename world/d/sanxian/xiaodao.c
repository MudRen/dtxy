inherit ROOM;
void create()
{
        set("short", "С��");
        set("long", @LONG
����СС�ĵص���Լ���߰˳ߣ��պÿ����ݵ���һ���˵����ӡ�
LONG
  );
  set("exits",([
        "out" : __DIR__"fangbian",
        "east" : __DIR__"chapeng",
      ]));  
set("objects", ([ /* sizeof() == 1 */
        __DIR__"bslong" : 1,
      ])); 
        set("no_magic",1);
        
        setup();
} 
