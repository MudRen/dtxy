// honghaier.c �캢��
// By Dream Dec. 20, 1996
#include <ansi.h>
inherit NPC;
inherit F_MASTER;
int ask_huohun();
string ask_fmtd();
void create()
{
	set_name("�캢��", ({ "honghai er" }));
	set("title", "�Ϻ�����֮ͽ");   
	set("long", @LONG
������ţħ��֮�ӣ����Ժö������Ϻ������շ���Ƣ��ȴ������ʲô��ת��
��ʹ��һ�ֵĺ�ǹ��������ǹ�������е��֣�Ѱ�����ǲ��������ġ�
LONG);
	set("gender", "����");
	set("age", 15);
	set("attitude", "heroism");
	set("max_kee", 750);
	set("max_gin", 600);
	set("max_sen", 750);
	set("force", 450);
	set("max_force", 300);
	set("force_factor", 20);
	set("max_mana", 350);
	set("mana", 500);
	set("mana_factor", 50);
	set("combat_exp", 240000);
	set("daoxing", 400000);

	set_skill("literate", 80);
	set_skill("spells", 100);
	set_skill("buddhism", 100);
	set_skill("unarmed", 60);
	set_skill("jienan-zhi", 60);
	set_skill("dodge", 80);
	set_skill("lotusmove", 80);
	set_skill("parry", 80);
	set_skill("force", 80);
	set_skill("lotusforce", 70);
	set_skill("staff", 50);
	set_skill("lunhui-zhang", 40);
	set_skill("spear", 300);
	set_skill("huoyun-qiang", 300);
	map_skill("spells", "buddhism");
	map_skill("unarmed", "jienan-zhi");
	map_skill("dodge", "lotusmove");
	map_skill("force", "lotusforce");
	map_skill("parry", "huoyun-qiang");
	map_skill("staff", "lunhui-zhang");
	map_skill("spear", "huoyun-qiang");
	set("chat_chance_combat", 40);
	set("chat_msg_combat", ({
		(: cast_spell, "bighammer" :),
		(: cast_spell, "jingang" :),
	}) );
	set("inquiry",([
      		"leave"    : (: ask_huohun :),
      		"��ħ"    : (: ask_fmtd :),
      			]));
	create_family("�Ϻ�����ɽ", 2, "����");

	setup();
	carry_object("/d/nanhai/obj/huojianqiang")->wield();
        carry_object("/d/qujing/bibotan/obj/zhanpao")->wear();
}

void attempt_apprentice(object ob)
{
	if (((int)ob->query_skill("buddhism", 1) < 50 )) {
		command("say " + RANK_D->query_respect(ob) + "�ķ����л�������������Ŭ�����ǣ�");
		return;
	}
	command("smile");
	command("say �ܺã��Ҿ������㣬ϣ������Ŭ�������������\n");

	command("recruit " + ob->query("id") );
	message("system", HIY"�ҷ����ֶ���һ������  "+this_player()->name()+HIW"
                 �Ϻ�����ɽ��������ǿ�ˡ�\n"NOR,users());
	return;
}

int ask_huohun()
{
	object me = this_player();
	object guanyin;
	if( me->query_temp("huohun/zhenshen") )	
	{
		command("say ��Ҳ���ȥ������������ʱ�����ԣ�");
		if( !objectp( guanyin = present("guanyin pusa",environment())) )
		{
			guanyin = new("/d/nanhai/npc/guanyin");
			guanyin->move(environment(me));
			message_vision(HIY"\n���г�������������������˭�ڴ����ҷ�Ҿ��أ���\n",me);
			message_vision(HIY"\n���������������Ʒ��˹�����\n",me);
		}
		message_vision(HIR"\n��������һ�����оŻ����ȣ���ס���㣡\n",me);
		guanyin->kill_ob(me);
		return 1;
	}
	else
		return 0;
}

string ask_fmtd()
{
	object me = this_player();
	if( me->query("betray/count") )
		return ("�����Ķ����޷�����ħͬ����ѧ��\n");
	if(me->query("family/family_name") != "�Ϻ�����ɽ" )
                return ("�㲻�������ӵ���!!\n");
        if(me->query("fmtd_cant"))
      		return ("���޷�������ߵķ�ħͬ����");
        if(me->query("fmtd_known") > 1 )
      		return ("��ħͬ���Ŀھ��㶼�Ѿ�֪���˰���");
      	if( me->query_skill("literate",1) < 200 )
		return ("�����ѧʶ�����������ħͬ����");
	if( me->query_skill("huoyun-qiang",1) < 200 )
		return ("�����ǹ�������������ħͬ����");
	if( me->query_skill("lotusforce",1) < 200 )
		return ("������ڹ������������ħͬ����");	
      	command("sigh");
      	if( me->query_temp("fmtd/zhenshen") == 1 )
      	{
      		command("say �ҵ���ĺ���Ϣ��");
      	}
      	else if( !me->query("fmtd_known") )
      	{
		me->set_temp("fmtd/zhenshen",1);
		command("say �ҽ������У��Է�ħ֮�����������κ���ħ��̫�����޷�����һ����");
		command("say ������ܰ���ȥ���ƶ�ȡ�����г����ҿ��Խ����г�֮��������������");
		command("say ��ʱ��������ɾͣ�����һͬ����");
		command("say ���ˣ���ֻ�轫���ж��е�С��ȡ�����ҾͿ����ˣ�");
	}
	else
	{
		message_vision(HIY"\nͻȻ�����ʢ�������������۾���\n"NOR,me);
		command("say �����Ѿ�֪���ˣ�����ȥ�𶥲�������");
		me->set_temp("fmtd/canwu",1);
		message_vision("��������һֻ�޴�ķ�����������$N��Զ����ȥ����\n",me);
		me->move("/d/southern/emei/jinding");
		message_vision("��������һ����$N���������������Ѿ�������ҽ𶥡�\n",me);
	}
	return ("���ͣ����ͣ�");
}

int accept_object(object me, object ob)
{
  	if( me->query_temp("fmtd/zhenshen") == 1 && me->query_temp("fmtd/num") < 5 )
	{	 
	 	if( ob->query("id") == "che" && ob->query("owner") == me->query("id") )
		{
	 		command ("nod "+me->query("id"));
      			me->add_temp("fmtd/num",1);
      			call_out("destroy", 2, ob);
		}
		if( me->query_temp("fmtd/num") == 5 )
		{
			message_vision(HIC"$N�����г��������еķ�λ�ںã���������һ�֣�Ʈ�������г������Ϸ���\n"NOR,this_object());
			command("say ����ϸ�ۿ����й��ķ��������������ˣ�һ����ָ�����㣡");
			message_vision(HIC"$N��ϥ����������һ������������⣬�����г��໥��ӳ��\n"NOR,this_object());
			message_vision(HIC"$n��$N�Ѿ���ʼ��������æ������Ϣ����ϸ��Ħѧϰ��\n"NOR,this_object(),me);
			message_vision(HIC"$NԽ��Խ�����ԣ�����������ʱ�䡣\n"NOR,me);
			me->start_busy(15);
			call_out("xiulian_finish",10,me,this_object());
		}
		return 1;
	}
	return 0;
}

void destroy(object ob)
{
        destruct(ob);
        return;
}

void xiulian_finish( object me, object who )
{
	if( !me || !who )
		return;
	message_vision(HIC"$N��������������һ�£������ع�������\n"NOR,me);
	message_vision(HIC"ֻ��$N���ڿ���$n����$N���������������Ȼ��Ϊ���г�����\n"NOR,this_object(),me);
	command("say �ҿ����������򣬸ղŽ����г���ħ�����ҶԷ�ħ֮�������������һЩ������������");
	message_vision(HIC"$N��$n����˵����һ����µĿھ���\n"NOR,this_object(),me);
	message_vision(HIC"$N��ϥ��������ʼ����$n�ոո���$N�Ŀھ���\n"NOR,me,this_object());
	me->start_busy(15);
	if( random(me->query("int")) > 20 - random( me->query("lunhui_zhuanshi") ) )
		call_out("finish1",10,me);
	else
		call_out("finish2",10,me);
	return;
}

void finish1( object me )
{
	message_vision(HIC"$N��ɫһ��죬һ���������֡�\n" NOR,me);
	message_vision(HIC"$N��ɫ������û��ͣ��ƺ�Ҫ�����������Ĺ���\n" NOR,me);
	message_vision(HIC"$N�����չ���վ����������캢������Ϲ���\n" NOR,me);
	me->delete_temp("fmtd");
	me->add("fmtd_known",1);
	message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"���캢��(hong haier)��" + me->name() + "����Ѱ�����г���������"+HIB"[��ħͬ��]"+HIC"��ѧ��\n\n\n"NOR,users());
	command("say ��ֻ�Ƿ�ħͬ���Ļ�����������պ����������������ң�");
	return ;
}

void finish2( object me )
{
	message_vision(HIC"$N��ɫһ��죬һ���������֡�\n" NOR,me);
	message_vision(HIC"$NͻȻ��¶ʹ��֮ɫ�����������Ϣ��\n" NOR,me);
	message_vision(HIR"$N�����չ���վ����������ɫ�Ұܣ������޷�����캢������$N�Ŀھ���\n" NOR,me);
	me->delete_temp("fmtd");
	me->set("fmtd_cant",1);
	message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"���캢��(hong haier)��" + me->name() + "����Ѱ�����г�����ϧ���Բ������޷�����"+HIB"[��ħͬ��]"+HIC"��ѧ��\n\n\n"NOR,users());
	command("sigh " + me->query("id"));
	command("say �����Բ��㣬ĪҪǿ�󣬷����书������㹻��ѧ���ˣ�");
	return ;
}