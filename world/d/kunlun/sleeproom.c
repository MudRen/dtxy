inherit ROOM;

void create ()
{
        set ("short", "��Ϣ��");
        set ("long", @LONG

���鶴�ĵ�����Ϣ�ҡ������൱��ª�����Ŵ���û�С�
LONG);

        //set("item_desc", (["bed" : "һ�ž��µĴ���(gosleep, gobed, bed)��\n", ]));
        //for look something.

        set("exits", 
        ([ //sizeof() == 4
                "northwest" : __DIR__"lingyunge",
                
        ]));
        
        set("sleep_room",1);      

        setup();
}
