// Room: /luohanta/tal6.c

inherit ROOM;

void create()
{
	set("short", "�޺���");
	set("long", @LONG


                        ��


LONG
	);
	set("exits", ([ /* sizeof() == 2 */
  "northdown" : __DIR__"tal5",
  "westup" : __DIR__"tal7",
]));
        set("objects", 
        ([ //sizeof() == 1
                __DIR__"npc/ll6" : 1,
     
        ]));
   set("no_clean_up", 0);
        setup();
   
}



int valid_leave(object me, string dir)
{
if (me->query("family/family_name") != "�Ϻ�����ɽ" && dir == "westup")
if(objectp(present("luo han", environment(me))))
return notify_fail("�޺����ֵ�ס�����ȥ·��\n");   
return ::valid_leave(me, dir);
}
