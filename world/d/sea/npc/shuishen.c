#include <ansi.h>

inherit NPC;
inherit F_MASTER;


void create()
{
        set_name("����", ({"ma zu","mazu","haishen","niangniang"}));

	set("long","��˵���ػ������Ů�񣬱��Ӻ������ƽ����\n");
    set("gender", "Ů��");
       set("age", 30);
       set("title", HIB"��������"NOR);
       set("class","dragon");
       set("attitude", "peaceful");
       set("shen_type", 1);
       set("combat_exp", 10000000);
       set("daoxing", 10000000);
       set("per", 40);
       set("str", 1000);
       set("max_kee", 6000);
       set("max_gin", 6000);
       set("max_sen", 6000);
       set("force", 16000);
       set("max_force", 8000);
       set("force_factor", 300);
       set("max_mana", 8000);
       set("mana", 16000);
       set("mana_factor", 400);
       set_skill("huntian-hammer", 300);
       set_skill("hammer", 300);
       set_skill("literate", 300);
       set_skill("unarmed", 300);
       set_skill("dodge", 300);
       set_skill("force", 300);
       set_skill("parry", 300);
       set_skill("fork", 300);
       set_skill("spells", 300);
	set_skill("seashentong", 300);
	set_skill("dragonfight", 300);
	set_skill("dragonforce", 250);
	set_skill("fengbo-cha", 300);
	set_skill("dragonstep", 300);
	map_skill("hammer", "huntian-hammer");
	map_skill("spells", "seashentong");
	map_skill("unarmed", "dragonfight");
	map_skill("force", "dragonforce");
	map_skill("fork", "fengbo-cha");
	map_skill("parry", "fengbo-cha");
	map_skill("dodge", "dragonstep");
	set("cfpl_known",2);
        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: cast_spell, "freez" :),
                (: exert_function, "shield" :),
                (: perform_action, "unarmed", "sheshen" :),
                (: perform_action, "unarmed", "shenglong" :),
                (: perform_action, "fork", "fengbo" :),
                (: perform_action, "fork", "cfpl" :),
                }) );
        create_family("��������", 1, "ˮ��");
	set_temp("apply/armor",250);
	set_temp("apply/damage",250);
	setup();

        carry_object("/d/sea/obj/longpao")->wear();
        carry_object("/d/sea/obj/tuotiancha")->wield();
}

void attempt_apprentice(object ob)
{	
       
       
       if (ob->query("obstacle/number") < 26) {
        command("say ��λ" + RANK_D->query_respect(ob) + "�㻹���ȳ�ȥ����һ���ɣ�\n");
        command("sigh");
        return;
        }

      if (((int)ob->query("daoxing") < 1000000 )) {
         command("say " + RANK_D->query_rude(ob) + "�������è�İ�ʽ��ô�ܰ���Ϊʦ����ȥ������!");
         return;
       }
       
       
       command("smile");
        command("say �ѵ�" + RANK_D->query_respect(ob) +
		"�д���־�������պ���Ŭ����Ϊ��ˮ�����⡣\n");
        command("recruit " + ob->query("id") );
	return;
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
              ob->set("class", "dragon");
        ob->set("title", HIB"�������ﴫ��"NOR);
}

void init()
{
	::init();
	add_action("do_lingwu", "lingwu");
}
string do_lingwu()
{
	object me=this_player();
	if( me->query("betray/count") )
		return ("�����Ķ����޷����������ѧ��\n");
	if(me->query("family/family_name") != "��������" )
                return ("�㲻������������!!\n");
        if(me->query("cfpl_cant"))
      		return ("������ʲ��ʺ�ѧϰ�˷����ˣ�");
        if( me->query("cfpl_known") > 1 )
      		return ("�˷����˵Ŀھ��㶼�Ѿ�֪���˰���");
      	if( !me->query("cfpl_lingwu") )
      		return ("�˷�����Ҳ��Ҫ˳�򽥽����㻹����ȥ����Ů�����޵аɣ�");
      	if( me->query_temp("lingwu") )
      		return ("���������򰡣�");
      	if( !me->query("cfpl_known") )
      	{
	      	if(me->query_skill("fork", 1) < 200 || me->query_skill("fengbo-cha", 1) < 200)
	                return ("��Ĳ淨���𻹲�����\n");
	        if(me->query_skill("hammer", 1) < 200 || me->query_skill("huntian-hammer", 1) < 200)
	                return ("��Ĵ������𻹲�����\n");
	        if(me->query_skill("unarmed", 1) < 200 || me->query_skill("dragonfight", 1) < 200)
	                return ("����Ʒ����𻹲�����\n");
	}
	else
	{
		if(me->query_skill("fork", 1) < 300 || me->query_skill("fengbo-cha", 1) < 300)
	                return ("��Ĳ淨���𻹲�����\n");
	        if(me->query_skill("hammer", 1) < 300 || me->query_skill("huntian-hammer", 1) < 300)
	                return ("��Ĵ������𻹲�����\n");
	        if(me->query_skill("unarmed", 1) < 300 || me->query_skill("dragonfight", 1) < 300)
	                return ("����Ʒ����𻹲�����\n");
	}
      	me->start_busy(20);
      	me->set_temp("lingwu",1);
      	message_vision(HIC"\n$N��ϥ��������ʼ����˷����ˣ�\n"NOR,me);
      	if( !me->query("cfpl_known") )
      	{
      		message_vision(HIC"\n����˵�����粨ʮ�����������������ˣ����պ�ˮ��Ϣ����֮�������ġ�\n"NOR,me);
      		message_vision(HIC"\n����˵������Ȼ���������˸������Ἰ�У������������о���ģ��������������޼���\n"NOR,me);
      		message_vision(HIC"\n����˵������Ȼ���Ѿ������˷粨ʮ����ľ��裬������ֻҪ�������򵽵��ڻ��ͨ�Ϳ����ˡ�\n"NOR,me);
      		
      		if( random(me->query("int")) > 20 - random( me->query("lunhui_zhuanshi") ) )
      			call_out("finish1",10,me);
      		else
      			call_out("finish2",10,me);
      	}
      	else
      	{
      		message_vision(HIC"\n����˵�����粨ʮ�����������������ˣ����պ�ˮ��Ϣ����֮�������ġ�\n"NOR,me);
      		message_vision(HIC"\n����˵���������촸������˵�������̹Ŵ�ۿ������õĻ���һ���ݱ������\n"NOR,me);
      		message_vision(HIC"\n����˵������Ȼ���Ѿ������˷粨ʮ����ͻ��촸���ľ��衣\n"NOR,me);
      		message_vision(HIC"\n����˵�������Ǵ����ر�����������ս���вִٸ������ͻ�����˿ɳ�֮����\n"NOR,me);
      		message_vision(HIC"\n����˵���������ھ�����Ҫ�������书�ڻ��ͨ��ʹ����֮��û��������\n"NOR,me);
      		me->delete("cfpl_lingwu");
      		if( random(me->query("int")) > 30 - random( me->query("lunhui_zhuanshi") ) )
      			call_out("finish1",10,me);
      		else
      			call_out("finish2",10,me);
      	}
      		
}

void finish1(object me)
{
	me->delete_temp("lingwu");
	if( !me->query("cfpl_known") )
	{
		me->set("cfpl_known",1);
		message_vision(HIC"\n$N����Ǳ˼��ʱ��ͻȻ��ߺ�ˮ����ӿ����\n"NOR,me);
		message_vision(HIC"\n$N����������������֮��������ǰ�ں���ç���������뺣ˮ��Ϊһ�������о��ٴ�ӿ�֡�\n"NOR,me);
		message_vision(HIC"\n$N��������׽��ˮ�����������������ڡ�\n"NOR,me);
		message_vision(HIC"\n$N��Ȼ���ʣ��粨ʮ�������ʽ�����Ժ��в�ͣ�������������Լ��ֲֳָ棬˳�����̡�\n"NOR,me);
		message_vision(HIC"\n$Nһ������������𣬺�ˮ����$N���ܻ���ı��ڡ�\n"NOR,me);
		message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"�����棨ma zu����"+ me->name()+"����粨ʮ���澫�裬����������"+HIY"�˷�����"+HIC"ǰ��ʽ��\n"NOR,users());
		tell_object(me,"����ߴ������������������Ŀǰ�����������ܻ���Ϊ�������պ��г��������ҡ�\n");
		message_vision(HIC"\nһ��ˮ����$N�ŵ�ӿ��$N��ʧ�����ˣ�\n"NOR,me);
		me->move("/d/sea/inside1");
		message_vision(HIC"\nͻȻһ��ˮ��ӿ��$N�������˳�������\n"NOR,me);
	}
	else
	{
		me->set("cfpl_known",2);
		message_vision(HIC"\n$N����Ǳ˼��ʱ��ͻȻ��ߺ�ˮӿ��һ�ɰ�������Ҫ��$N�߸�����\n"NOR,me);
		message_vision(HIC"\n$N������������һת�����˲��䣬˳�ź�ˮ֮��������ա�\n"NOR,me);
		message_vision(HIC"\n$N�����������㳡�Ǿ���һ��������ѪҺ���ڣ����������ٴμ�����ת���͡�\n"NOR,me);
		message_vision(HIC"\n$N��Ȼ���򣬰���г�����������㵸�䣬�����������书����ʹ��������ʱ��Ȼ��ɣ���¶���������\n"NOR,me);
		message_vision(HIC"\n$Nһ������������ͻȻ��ת���£�����������׹�������ף�������������ֱ�����¡�\n"NOR,me);
		message_vision(HIC"\n$Nֻ��ײ��һ����ˮ�������֮�ϣ��������仯����$N�ľ�����$Nһ������˳�����¡�\n"NOR,me);
		message_vision(HIC"\nֻ�����溬Ц����$N��$N�����°ݡ�\n"NOR,me);
		message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"�����棨ma zu����"+ me->name()+"���ڽ�������ѧ�ڻ��ͨ����ȫ������������ѧ"+HIY"�˷�����"+HIC"��\n"NOR,users());
		message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"�����㣨ao guang�������������˭������������Ұ����\n"NOR,users());
		tell_object(me,"����ߴ���������������мǣ��˷������������ף������ƾ٣����򲻿���������\n");
		message_vision(HIC"\nһ��ˮ����$N�ŵ�ӿ��$N��ʧ�����ˣ�\n"NOR,me);
		me->move("/d/sea/inside1");
		message_vision(HIC"\nͻȻһ��ˮ��ӿ��$N�������˳�������\n"NOR,me);
	}
	return;	
}

void finish2(object me)
{
	me->delete_temp("lingwu");
	me->delete("cfpl_lingwu");
	me->set("cfpl_cant",1);
	message_vision(HIC"\n$NǱ˼��ʱ��ͷ����һƬ���ң����ܺ�ˮ�������ѣ�$N�ղ����ٴ���ᵽ�������ϡ�\n"NOR,me);
	message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"�����棨ma zu����"+ me->name()+"�ղ������������ѧ���裬��"+HIY"�˷�����"+HIC"�����������ϧ��̾��\n"NOR,users());
	command("sigh");
	message_vision(HIC"\n�������˸��ھ�������һ�ӣ�\n"NOR,me);
	message_vision(HIC"\nһ��ˮ����$N�ŵ�ӿ��$N��ʧ�����ˣ�\n"NOR,me);
	me->move("/d/sea/inside1");
	message_vision(HIC"\nͻȻһ��ˮ��ӿ��$N�������˳�������\n"NOR,me);
	return;	
}