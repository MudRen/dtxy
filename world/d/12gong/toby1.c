// by HAPP@YSZZ

inherit ROOM;

void create ()
{
        set ("short", "ɽ·");
        set ("long", @LONG

����������򹬵�·�ϣ�ֻ��ǰ����Կ��������İ��������ڰ���
ƥ�Ƿ��ϣ�
LONG);


        set("exits", ([
 "southup"    :       __DIR__"toby2",
// "southwest" : "/d/kaifeng/wutaishan/wutx",
"southwest" : "/d/southern/wutai/guandao3",
        ]));

        set("objects", 
        ([ //sizeof() == 1
                __DIR__"npc/cike" : 1,
        ]));
		set("outdoors", "12gong");
        setup();
}
