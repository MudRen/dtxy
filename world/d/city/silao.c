// ��������   Beeby 7/17/2000

#include <ansi.h>

inherit ROOM;


void create ()
{
        set ("short", "��������");
        set ("long", @LONG
    �����ǳ������й�Ѻ�ط��ĵط���ǽ����մ����Ѫ����ԶԶ�������� 
������Ĳҽ���, �κ��˽�������ط����������ȥ�ˡ�����ǽ����Щ��
�Ƚ��ɶ���
LONG);
        set("exits", 
        ([ //sizeof() == 0
        ]));
        set("no_clean_up", 0);
	set("no_escape",1);
        setup();
}

void init()
{
        add_action("do_wa", "wa");
	add_action("do_wa", "dig");
}

int do_wa(string arg)
{
	string msg;
	if (this_player()->is_busy())
	 return notify_fail("����æ����!\n");
	if (this_player()->query("kee")<50)
	 return notify_fail("���Ѿ�ƣ�����ˣ���������Ϣһ�°�!\n");
	this_player()->add("kee",-50);
	msg="$N���ڵ���ƴ������������ͼ�ڳ�һ��ص�����\n";
	message_vision(msg,this_player());
	call_out("do_end",3,this_player());
	this_player()->start_busy(3);	
	return 1;
}

int do_end(object me)
{
	string msg;
       int i=random(5);
	mixed* file;
	switch (i)
	{
	   case 0:
	   {
	     file=get_dir(__DIR__"*.c");
	     if (sizeof(file))
	     {
	     msg="��֪���˶೤ʱ��,$N������ͨ��һ���ص���\n"+
		 "$N�Ͻ����˳�ȥ��\n";
	     message_vision(msg,me);
	     msg=file[random(sizeof(file))];
	     if (msg=="ground") msg="center";
              else if (msg=="prison") msg="center";
              else if (msg=="guan") msg="center";
 	     me->move(__DIR__+msg);
	     msg="ֻ���ú��һ�����ص������ˡ�\n";
	     message_vision(msg,me);
	     if (me->query("mystartroom"))
	       me->set("startroom",me->query("mystartroom"));
	     else 
	       me->set("startroom","/d/city/kezhan");
	     break;
	     }
	   }
	   default:
	   {
	     msg="����ͻȻ����һ��Ų�����$N�ŵøϽ��ѵص��������ˡ�\n";
	     message_vision(msg,me);
	   }
	}
	return 1;
}
