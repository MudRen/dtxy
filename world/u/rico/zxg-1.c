inherit ROOM;
void create ()

{
     set("short","�ɾ�");
     set("long",@LONG

���ﲻ֪����������ɽ�е�һ��ɽ�ȡ�
Զ����ɽ���룬���ƻֺ룬���ܲ��ɴ�أ������дС�
�Ա�һ̶��ˮ����Ӱ�������ɽɫ����߻���ʱ
���������޾�������һ���˼��ɾ���
��-----��Щ����ֽ�����Ĳ�������
LONG);
      set("exits", ([ /* sizeof() == 1 */
      "west" : __DIR__"zhaoxiangguan",
]));
      set("objects", (["/u/rico/obj/dan":1,]));
      setup();
  set("no_fight", 1);
  set("outside", 1);
  set("no_magic", 1);

        setup();
}

