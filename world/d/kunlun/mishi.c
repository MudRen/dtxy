inherit ROOM;

void create ()
{
  set ("short", "����");
  set ("long", @LONG

    ����������һ��ʯ�ң��˴��ܰ��������ʺ��ɼ�����������
ԭʼ����Ϊ�˰������������õ��ӽ������ڴ˽Ӵ����������
���ǡ�

LONG);

  set("exits", ([
        "north"   : __DIR__"houtang",
        "southeast"   : __DIR__"dadian",
      ]));
  set("objects", ([
                __DIR__"npc/jiang" : 1,
     ]));

  setup();
  set("valid_startroom", 1);
}
