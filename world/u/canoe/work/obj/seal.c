#include <ansi.h>

inherit ITEM;
string *list=({/*"yg-qiankun","yg-jianmang","yg-jianzhang","yg-zxzx",*/
		"yg-sanshou",
               /*"yg-xueshan",
                "yg-ba","yg-jldl","yg-xiao","yg-yanluo","yg-kunlun","yg-sanban",
	       */});

void create()
{
        set_name("ץ���", ({"ghost seal", "seal", "paper"}));
	set_weight(100);
	if(clonep())
    		set_default_object(__FILE__);
  	else {

        set("long","һ�Ż����˷�����ҷ�ֽ��\n");
        set("unit", "��");
        set("value", 0);
	set("no_put",1);
	set("no_sell",1);
	}
	setup();
}

string long()
{
	if(stringp(query("desc")))
		return "һ�Ż������������ҷ�ֽ������(burn)��ץ��\n"+
		"ֻ�����滭�ţ�\n"+HIR+query("desc")+NOR+"\n��������ϴ��ƺ���"+HIY+query("where")
		+NOR+"���ֹ���\n�������ͣ�"+query("kind")+"��\t�Ѷȣ�"+query("level")+"��\t������"+query("times")+"��\n";
}

void init()
{
	add_action("do_burn", "burn");
if( (int)this_object()->query("created") != 1 )
	{
		this_object()->set("created", 1);
		remove_call_out ("destroy_it");
		call_out ("destroy_it", 300);//5 min

	}
}
void destroy_it()
{
	message_vision("һ��紵����" + (string)this_object()->query("name") + "ƬƬ���䣬����ȥ��\n", environment(this_object()));
	destruct(this_object());
}

int do_burn(string arg)
{
	object room,guai,me;
	me=this_player();
	
	if(!arg||!id(arg))
		return notify_fail("��Ҫ��ʲô��\n");
	this_object()->set("times",(int)this_object()->query("times")-1);
	if(query("times")<1)
	{
	destroy_it();
	}
	message_vision(RED"$N��һ������ħ��ֿ���������һ�ӣ�������һ��ץ���������\n\n"NOR, me);
	if(!query("master")||query("master")!=me)
	{
		message_vision("���ʲô��û�з�����\n", me);
		destroy_it();
		return 1;
	}
	room=environment(me);
	if(file_name(room)+".c"!=query("file_name"))
	{
		message_vision("���ʲô��û�з�����\n", me);
		return 1;
	}
	guai = new(__DIR__+"npc/"+list[random(sizeof(list))]);
	if(guai->move(room))
	{
	guai->copy_status(me,(int)this_object()->query("level"));
	guai->set("owner", me);
	guai->set("kind",me->query("canoetask/kind"));
	guai->set("level",(int)this_object()->query("level"));
	me->set("canoetask/guai",guai);
       	message_vision(HIB"ֻ��һ������������$N��ץ������ճ�ԭ�Ρ�\n"NOR,guai,me);
	destruct(this_object());
	return 1;
	}
	else write("���ָ��Ʋ��ɹ���\n");
	return 1;
}
