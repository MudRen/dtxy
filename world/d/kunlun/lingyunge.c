inherit ROOM;

void create ()
{
  set ("short", "���Ƹ�");
  set ("long", @LONG

    ����������̻Ի��������𣬸������������룬��ǽ�
���ܣ�������ǽ���ԧ��˫˫�Զԣ�������һ�����������
̨�����Ϸ�����Ϣ�ҡ����洫��������������
LONG);

  set("exits", ([
        "southeast" :  __DIR__"sleeproom",         "north"   : __DIR__"wuchang",
        "south"   : __DIR__"shijie2",
      ]));
  set("objects", ([
/* sizeof() == 1 */
  "/d/kunlun/npc/jinzha" : 1,
     ]));

  setup();
}
