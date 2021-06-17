// tomcat
#include <ansi.h>
inherit NPC;
string ask_piaoxue();
void create()
{
	set_name(HIY"��"HIM"��"HIC"����"NOR, ({"fenghuang mingwang", "fenghuang", "mingwang", "wang"}));
	//set("gender", "����" );
	set("age", 45);
	set("per", 100);
	set("str", 100);
	set("kar",40);
	set("long", "�����ǰ���֮������ˡ�");
	set("class", "yaomo");
	set("combat_exp", 100000000);
	set("daoxing", 100000000);

	set("attitude", "peaceful");
	set("family/family_name","��ѩɽ");
	set_skill("unarmed", 1000);
	set_skill("cuixin-zhang", 1000);
        set_skill("dodge", 1000);
	set_skill("xiaoyaoyou", 1000);
	set_skill("parry", 1000);
        set_skill("sword", 1000);
        set_skill("bainiao-jian", 1000);
	set_skill("blade", 1000);
	set_skill("bingpo-blade", 1000);
	set_skill("throwing", 1000);
        set_skill("force", 1000);   
	set_skill("ningxie-force", 1000);
        set_skill("literate", 1000);
	set_skill("spells", 1000);
	set_skill("dengxian-dafa", 1000);
	map_skill("spells", "dengxian-dafa");
	map_skill("force", "ningxie-force");
	map_skill("unarmed", "cuixin-zhang");
	map_skill("sword", "bainiao-jian");
	map_skill("parry", "bainiao-jian");
	map_skill("throwing", "bainiao-jian");
	map_skill("blade", "bingpo-blade");
	map_skill("dodge", "xiaoyaoyou");
	set("piaoxue_known",3);
	set("max_kee", 100000);
	set("max_sen", 100000);
	set("force", 30000);
	set("max_force", 15000);
	set("mana", 30000);
	set("max_mana", 15000);	
	set("force_factor", 250);
	set("mana_factor", 751);
	set_temp("apply/armor",1000);
	set_temp("apply/damage",500);
	set_temp("apply/attack",250);
	set("inquiry",([
      		"Ʈѩ��ʽ": (: ask_piaoxue :),
      		]));
	set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
		(: cast_spell, "niepan" :), 
        	(: perform_action, "blade", "piaoxue" :),
                (: cast_spell, "juanbi" :),

       }) );
	setup();
	carry_object("/d/obj/cloth/choupao")->wear();
	carry_object("/d/obj/weapon/blade/handudao-redblue")->wield();
}

void init()
{
        object ob = this_player();
        message_vision(HIR"$N����ǰһƬ��죬һ������ǵص�������$Nӿ����\n"NOR,ob);
        if( !ob->query_temp("meet") )
        {
        	ob->set_temp("meet",1);
        	ob->unconcious();
        }
}


string ask_piaoxue()
{
	object book;
	object me=this_player();
	if( me->query("betray/count") )
		return ("�����Ķ����޷������ѩɽ��ѧ��\n");
	if(me->query("family/family_name") != "��ѩɽ" )
                return ("�㲻���Ҵ�ѩɽ����!!\n");
        if( me->query("piaoxue_known") == 3 )
      		return ("ѩɽ��ѧ�����Ѿ�ȫ�������ˣ�");
        if( me->query("piaoxue_known") < 2 )
      		return ("�ҵĹ��������˵����̫����ˣ�����ȥ���ҵܵܰɣ�");
        if(me->query("piaoxue_cant"))
      		return ("��ϧ����ϧ��������Եѧ��һ���ѧ��");
	if( me->query_skill("ningxie-force",1) < 300 )
		return ("����Ѫ��̫�ͣ�ǿ����ѧ�������к���");
	if( me->query_skill("bingpo-blade",1) < 300 )
		return ("����Ǻ���̫�ͣ�ǿ����ѧ�������к���");
	if( me->query_skill("dengxian-dafa",1) < 300 )
		return ("����ɴ�̫�ͣ�ǿ����ѧ�������к���");
	if( me->query_temp("piaoxue1/lingwu") == 1 )
		return ("���ǰ�������ɣ�");
	me->start_busy(20);
	command("say �ţ������������������۹ⲻ���յĺõ��ӡ�");
	command("say ��ȸҲ������ˣ�ֻ��ʱ��̫�̣��������������ѧ�ľ�Ҫ����Ȼ������Ե���Ҿͽ���һ�㡣");
	message_vision(HIC"\n$N��ϸ����$n�Ľ��⣬����ϲ����ɫ����ѩɽ���书���˸������ᣡ\n" NOR, me,this_object());
	message_vision(HIC"\n$N������������ѧ�Ŀ�����磬������Ȼ���ң�\n\n" NOR, me,this_object());
	me->set_temp("piaoxue1/lingwu",1);
	call_out("check",10,me);
	return ("�����е����ԣ�");
}

void check(object me)
{
	me->delete_temp("piaoxue1/lingwu");
	message_vision(HIC"\n$N����Ԫ�񽥽��뿪���壬��������У������һ�У�\n" NOR, me);
	message_vision(HIC"\n$N���������ѩ�еĴ�ɫ����������е��滨��\n" NOR, me);
	message_vision(HIC"\n$N������������ȥ��ȴ���ַ�������ٲ�������һ���һ�\n" NOR, me);
	message_vision(HIC"\n���������������Ȼ������º͡�\n" NOR, me);
	if( random(me->query("int")) > 30 - random( me->query("lunhui_zhuanshi") ) )
	{
		me->add("piaoxue_known",1);
		message_vision(HIC"\n$N��Ȼ�����ˣ�����������������\n" NOR, me);
		message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"���������(fenghuang mingwang)��" + me->name() + "���Թ��ˣ����ҵ�ָ���¶���������������ȫ������"+HIW"[Ʈѩ��ʽ]"+HIC"��\n\n\n"NOR,users());
	}
	else
	{
		me->set("piaoxue_cant",1);
		message_vision(HIC"\n$N�������Դ�Ҳû�����ף�����һ���������˹�����\n" NOR, me);
		message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"���������(fenghuang mingwang)��" + me->name() + "�����ҵ�֪������ϧ���Բ�����δ������"+HIW"[Ʈѩ��ʽ]"+HIC"��ȫ��������\n\n\n"NOR,users());
	}
	return;
}