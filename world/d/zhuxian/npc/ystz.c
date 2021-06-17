#include <ansi.h>
inherit NPC;

string ask_pozhen();
void create()
{
    set_name(HIW "Ԫʼ����" NOR, ({"yuanshi tianzun", "tianzun", "yuanshi"}));
    set("title", HIR "����֮��" NOR);
    set("long", "����֮�ף������ޱߡ�\n");
    set("gender", "����");
    set("age", 13500);
    set("str", 40);
    set("per", 40);
    set("attitude", "peaceful");
    set("combat_exp", 10000000);
    set("daoxing", 10000000);
    set("eff_kee", 10000);
    set("eff_sen", 10000);
    set("max_kee", 10000);
    set("max_sen", 10000);
    set("sen", 10000);
    set("kee", 10000);
    set("max_force", 10000);
    set("max_mana", 10000);
    set("mana", 10000);
    set("force", 20000);
    set("force_factor",  500);
    set("mana_factor", 500);
    set_skill("dao", 351 );
    set_skill("zhenyuan-force", 351);
    set_skill("spells", 321);
    set_skill("force", 301);
    set_skill("moonshentong", 351);
    set_skill("whip", 301);
    set_skill("staff", 301);
    set_skill("blade", 301);
    set_skill("spear", 301);
    set_skill("hammer", 301);
    set_skill("buddhism", 351);
    set_skill("taiyi", 351);
    set_skill("lotusforce", 351);
    set_skill("wuxiangforce", 351);
    set_skill("xuanzong-force", 351);
    set_skill("yuxu-spells", 351);
    set_skill("moonforce", 351);
    set_skill("stick", 301);
    set_skill("dodge", 301);
    set_skill("unarmed", 301);
    set_skill("parry", 301);
    set_skill("sword", 251);
      map_skill("force", "wuxiangforce");
      map_skill("spells", "dao");
	set("inquiry",([
      "����": (: ask_pozhen :),
      ]));
    set("chat_chance_combat", 60);
    set("chat_msg_combat", ({
        (: cast_spell, "light" :),
        (: cast_spell, "thunder" :),
        (: cast_spell, "dingshen" :),
        (: cast_spell, "fenshen" :),
(: exert_function, "jldl" :)
}));
      setup();
   
}

int accept_fight(object me)
{
        write("������Ҳ���\n");
        return 0;
}

int recognize_apprentice(object me)
{
      object ob = this_player();
      
        if (!(int)ob->query_temp("mark/��"))
             return notify_fail( HIR "������" HIW "Ԫʼ����" HIR "��ɱ���㣡\n"NOR);
        if( ( ob->query("family/family_name") != "����ɽ���Ƕ�"
            && ob->query("family/family_name") != "����ɽ���鶴"
            && ob->query("family/family_name") != "�Ϻ�����ɽ"
            && ob->query("family/family_name") != "�¹�"
            && ob->query("family/family_name") != "��ׯ��")
            || ob->query("combat_exp")  < 2000000 ) 
             return notify_fail( HIR "������" HIW "Ԫʼ����" HIR "��ɱ���㣡\n"NOR);

             ob->add_temp("mark/��", -1);
               return 1;
}

int accept_object(object me,object ob)
{
       	if( me->query_temp("quzhu/zhuxian") == 1 && ob->query("id") == "zhuxian spear" )
       	{
       		command("nod");
       		me->add_temp("quzhu/get",1);
       		call_out("destroy", 2, ob);
       	}
       	if( me->query_temp("quzhu/zhuxian") == 1 && ob->query("id") == "juexian blade" )
       	{
       		command("nod");
       		me->add_temp("quzhu/get",1);
       		call_out("destroy", 2, ob);
       	}
       	if( me->query_temp("quzhu/zhuxian") == 1 && ob->query("id") == "luxian stick" )
       	{
       		command("nod");
       		me->add_temp("quzhu/get",1);
       		call_out("destroy", 2, ob);
       	}
       	if( me->query_temp("quzhu/zhuxian") == 1 && ob->query("id") == "xianxian whip" )
       	{
       		command("nod");
       		me->add_temp("quzhu/get",1);
       		call_out("destroy", 2, ob);
       	}
       	if( me->query_temp("quzhu/get") > 3 )
       	{
       		me->delete_temp("quzhu/get");
       		me->delete_temp("quzhu/zhuxian");
       		message_vision(HIW"ֻ��$N"+HIW"���ļ��������������ڱ���������һ�������ҫ�۵İ׹�������$N"+HIW"�������Ѿ�����һ�Ѱ�ɫ������\n"NOR, this_object());
       		if( random(me->query("int")) > 25 - random( me->query("lunhui_zhuanshi") ) )
      		{
      			me->add("quzhu_known",1);
	  		message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"��Ԫʼ����(yuanshi tianzun)��" + me->name() + "�´�ʮ���������ţ����ı�����������"+HIW"���ɽ�"+HIC"����"+HIR"[������ħ]"+HIC"��������ˣ�\n\n\n"NOR,users());
      			command("say �����Ҫ�������ܣ�����������֮�°ɣ�");
      		}
      		else
      		{
      			me->set("quzhu_cant",1);
	  		message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"��Ԫʼ����(yuanshi tianzun)��" + me->name() + "�´�ʮ���������ţ����ı�����������"+HIW"���ɽ�"+HIC"��ȴ�޷���������"+HIR"[������ħ]"+HIC"��\n\n\n"NOR,users());
      			command ("say ��ĪҪ���ģ��ܿ�����ٴγ����ˣ�");
      		}
       	}
       	return 1;
}
void destroy(object ob)
{
        destruct(ob);
        return;
}
   
string ask_pozhen()
{
	object me=this_player();
	if( me->query("betray/count") )
		return ("�����Ķ����޷�����\n");
	if(me->query("family/family_name") != "����ɽ���鶴" )
                return ("�㲻�������ص��ӣ��޷�����!!\n");
        if(me->query("quzhu_cant"))
      		return ("��Ļ�Ե�������޷�����");
        if( me->query("quzhu_known") > 2 )
      		return ("����ķ����㶼�Ѿ�֪���ˣ��ѻ����������˰ɣ�");
      	if( me->query_temp("quzhu/mo") && me->query_temp("mark/��") > 2 )
      	{
      		me->delete_temp("mark");
      		me->delete_temp("quzhu/mo");
      		if( random(me->query("int")) > 20 - random( me->query("lunhui_zhuanshi") ) )
      		{
      			me->add("quzhu_known",1);
	  		message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"��Ԫʼ����(yuanshi tianzun)��" + me->name() + "����ʮ������ħ�����������"+HIR"[������ħ]"+HIC"��\n\n\n"NOR,users());
      			return ("�����Ҫ�������ܣ�����������֮�°ɣ�");
      		}
      		else
      		{
      			me->set("quzhu_cant",1);
	  		message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"��Ԫʼ����(yuanshi tianzun)��" + me->name() + "����ʮ������ħ���ϧ���Բ������޷�����"+HIR"[������ħ]"+HIC"��\n\n\n"NOR,users());
      			return ("��ĪҪ���ģ��ܿ�����ٴγ����ˣ�");
      		}
      	}
      	if( !me->query("quzhu_known") )
      	{
		me->set_temp("quzhu/mo",1);
		return ("����ȥ���н�����xiang������ħ��������ң�");
	}
	else if( me->query("quzhu_known") == 1 )
	{
		me->set_temp("quzhu/zhuxian",1);
		return ("�����ĽǷֱ��ɷ���ˮ�񡢻����������������ɱޡ����ɵ���¾�ɹ�������ǹ����ȥ���Ҷ�����");
	}
	else
	{
		me->set_temp("quzhu/ttjz",1);
		return ("��������Ľ��Ѿ����䣬��ʣ�����ĵ�ͨ������ˣ�������ʦ�ܣ����޷����Գ��֣����鷳���ˣ�");
	}
}