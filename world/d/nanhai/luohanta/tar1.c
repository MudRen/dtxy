
inherit ROOM;

void create ()
{
        set ("short", "�޺���");
        set ("long", @LONG


                        ��


LONG);

        //set("item_desc", ([" *** " : " *** ", ]));

        set("exits", 
        ([ //sizeof() == 4
        
         "southup" : __DIR__"tar2",
         "out" : __DIR__"tarout",
]));
        set("objects", 
        ([ //sizeof() == 1
                __DIR__"npc/lr1" : 1,
     
        ]));
   set("no_clean_up", 0);
        setup();
   
}



int valid_leave(object me, string dir)
{
if (me->query("family/family_name") != "�Ϻ�����ɽ" && dir == "southup")
if(objectp(present("luo han", environment(me))))
return notify_fail("�޺����ֵ�ס�����ȥ·��\n");   
return ::valid_leave(me, dir);
}
