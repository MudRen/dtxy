// edited by mind
inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
����ʯ·�ߣ��з��Ӵ���һ��������˼���ľ�����������ʣ�����
��Щ±ζС�ԣ�������������⡣�����£�ͣ�����������Ĵ󳵣���ƥ��
�������Ľ����������»��������꣬�������֡�
LONG
        );
        set("exits", ([ 
                "north" : "/d/kaifeng/chen1",
        ]));
     set("objects", ([
        
       ]) ); 
        
        setup();
        replace_program(ROOM);
}
