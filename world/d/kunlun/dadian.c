inherit ROOM;

void create()
{
        set("short", "���");
        set("long", @LONG
    ���������鶴�Ĵ��������ʮɫ����̻Իͣ���ʱ��
�������������ڴ˴����ٴ��ɼ�Ժ�д���͸͵���������䣬
ɷ��Ư�����


LONG );
        set("exits", ([
                "south" : __DIR__"wuchang",
                "northwest" : __DIR__"mishi",
        ]));
          set("kunlun", 1);
  set("objects", ([ // sizeof() == 1 //
 __DIR__"npc/luya" : 1, 
__DIR__"npc/zhangmen" : 1, 
 ]));
  set("valid_startroom", 1);
  setup();
}

