// by HAPP@YSZZ

inherit ROOM;
int block_cmd(string);
void create ()
{
        set ("short", "��һ��������");
        set ("long", @LONG

    �غ����ǹ���������˹��������������飬��������һ��˫��̥��������ȴ����
���Ĺ�����ŵ���жλ����飬�������������ϳ�������ӭ��ŵ��Ϊ����������ŵ����
�������Լ��ĺ��Ӻ��˾���Ҫɱ��ǰ���������������µ�Ψһ˫��̥��(���������
��˼�������Ǻ���)��������ռ��ʦ�������״��������ǰ���������ĺ����͸���˹��
��Ʒ�����񽫴�ŭ������꽫�ּ��ġ�������֪���������˹��ȣ�������˹������
�ϵĻƽ�ĵ��ȥ��������������ձ˷������ٶ�̫�죬���õ���󺣣�ĵ���һ�߻�
ͷ�����ã�һ���ػ��Ÿ�磬���γ��ֽ��ĵ������

LONG);


        set("exits", ([
        "northup"    :       __DIR__"by2jn1",
            "eastdown"  :       __DIR__"toby2",
        ]));

        set("objects", 
        ([ //sizeof() == 1
                __DIR__"npc/baiyang" : 1,
        ]));
        set("outdoors", "12gong");
        setup();
}
int valid_leave(object me, string dir)
{
           
		  if (me->query_temp("12gong/cike") == "done")
	{if ( present("mu") && dir == "northup" )
           return notify_fail("��������Цһ�����ȹ��������˵��\n");
	}
		  
		  if (me->query("12gong/baiyang") != "done")
	{
			  if ( present("mu") && dir == "northup" )
			  return notify_fail("������΢΢һЦ˵��: ��Ȼ���˺αؼ�����?\n");
	}
	     
		 return ::valid_leave(me, dir);
}



void init()
{
    add_action("block_cmd", "", 1);
}
int block_cmd(string args)
{
string verb;
verb = query_verb();
    if (verb == "recall") return 1;
    return 0;
}
