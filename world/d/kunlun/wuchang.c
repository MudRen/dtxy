inherit ROOM;

void create ()
{
        set ("short", "���䳡");
        set ("long", @LONG

    �������鶴ǰ��һ��ƽ�أ������ɵ�������֮�á�������ͯ
������ϰ������

LONG);

        //set("item_desc", ([" *** " : " *** \n", ]));
        //for look something.

        set("exits", 
        ([ //sizeof() == 4
                "south" : __DIR__"lingyunge",
                "north" : __DIR__"dadian",
        ]));
        
        set("objects", 
        ([ //sizeof() == 1
               __DIR__"npc/xiaotong" : 2,
        ]));


        set("outdoors", "kunlun");

        setup();
}
