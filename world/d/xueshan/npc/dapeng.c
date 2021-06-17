// dapeng.c...weiqi, 97.09.27.

inherit NPC;
inherit F_MASTER;
string ask_piaoxue();
void create()
{
	set_name("��������", ({"dapeng mingwang", "dapeng", "mingwang", "wang"}));
	set("title", "ѩɽ֮��");
	set("gender", "����" );
	set("age", 45);
	set("per", 30);
	set("str", 30);
	set("long", "��λ����������ȷ����������˵��������������Ҳ�е����ݹ�ϵ��\n���������ġ��˾ˡ������������ֿ�ȸ���������ˣ�ȴҲ�������࣬\n��������֮�ʸ����Ž��������ƽ������ľ��Ǻ��С�\n");
	set("class", "yaomo");
	set("combat_exp", 1800000);
	set("daoxing", 3000000);

	set("attitude", "peaceful");
	create_family("��ѩɽ", 1, "��ʦ");
	set("rank_info/respect", "����");
	set_skill("unarmed", 200);
	set_skill("cuixin-zhang", 200);
	set_skill("dodge", 200);
	set_skill("xiaoyaoyou", 200);
	set_skill("parry", 200);
	set_skill("sword", 200);
	set_skill("bainiao-jian", 200);
	set_skill("blade", 200);
	set_skill("bingpo-blade", 200);
	set_skill("throwing", 200);
	set_skill("force", 200);   
	set_skill("ningxie-force", 200);
	set_skill("literate", 150);
	set_skill("spells", 200);
	set_skill("dengxian-dafa", 200);
	map_skill("spells", "dengxian-dafa");
	map_skill("force", "ningxie-force");
	map_skill("unarmed", "cuixin-zhang");
	map_skill("sword", "bainiao-jian");
	map_skill("blade", "bingpo-blade");
	map_skill("dodge", "xiaoyaoyou");

	set("max_kee", 3500);
	set("max_sen", 3500);
	set("force", 3500);
	set("max_force", 1800);
	set("mana", 4000);
	set("max_mana", 2000);	
	set("force_factor", 120);
	set("mana_factor", 100);

	set_temp("apply/damage", 50);
	set_temp("spply/armor", 50);
	set_temp("apply/dodge", 50);
	set("inquiry",([
      		"����": (: ask_piaoxue :),
      		]));
       set("chat_chance_combat", 50);
       set("chat_msg_combat", ({
                (: cast_spell, "juanbi" :),
                (: cast_spell, "tuntian" :),
                (: perform_action, "sword", "chaofeng" :),

       }) );
            setup();
	carry_object("/d/obj/cloth/choupao")->wear();
	carry_object("d/obj/weapon/sword/qinghong")->wield();
}

void attempt_apprentice(object ob)
{
	if( (string)ob->query("class")=="bonze" && (string)ob->query("gender")=="����"  )
	{
		command("kick " + ob->query("id"));
		command("say ���ߣ����ߣ���һ�������о�������\n");
		return;
	}

	if( (string)ob->query("family/family_name")=="��ѩɽ" ){
		if( (int)ob->query("family/generation") > 3   ){
			command("say û���Ĵ󻤷����Ƽ����������ѿ��ǡ�\n");
		}
		else {
			if( (int)ob->query("daoxing")+(int)ob->query("combat_exp") >= 500000 ){
				command("nod ");
				command("say �ã�" + RANK_D->query_respect(ob) + "�úø��Ҹɣ��������п�Ϊ��\n");
				command("recruit " + ob->query("id") );
			}
			else {
				command("say �㻹������ʨ���������������Űɡ�\n");
			}
		}
	}

	else{
		command("hmm");
		command("say ��λ" + RANK_D->query_respect(ob) + "���ڱ��ſ�û��һ��������¡�\n");
	}

	return;
}

int recruit_apprentice(object ob)
{
	if( ::recruit_apprentice(ob) )
		ob->set("class", "yaomo");
}

void init()
{       
	object ob=this_player();

	::init();
	if ( ((string)ob->query("gender")=="����") && ((string)ob->query("class")=="bonze") && (random(3) > 1) )
	{
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
}
void greeting(object ob)
{
	if( !ob || environment(ob) != environment() ) return;
	
	switch( random(1) ) {
		case 0:
			command("kick " + ob->query("id"));
			command("say ����ͺ��");
			break;
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
        if(me->query("piaoxue_cant"))
      		return ("��������޹أ�");
        if( me->query("piaoxue_known") )
      		return ("������û���ܽ�����ˣ���ȥ�����ֳ��ɣ�");
	if( me->query_skill("ningxie-force",1) < 200 )
		return ("����Ѫ��̫�ͣ��Կ�������Σ���������ģ�");
	if( me->query("piaoxue/handu") == 1 )
		return ("��������ɫ�������԰ɣ�ע��ѭ�򽥽���");
	if( me->query("piaoxue/handu") == 2 )
		return ("�ܺã�������˫ɫ�������԰ɣ�");
	command("say �ã���������һֱ������Ǳ�����п��Ʋ���֮����");
	command("say �������һ����С�����˺���������ͨ���������������Ա��������Կ����ں�����Ҳ�ܽ����Щ���顣");
	command("say �Ҵ�ѩɽ���������������������Ѫ�񹦵���Ϊ��ͨ���������������������������Ƴɡ�");
	me->set("piaoxue/handu",1);
	return ("�㲻��ʹ����ɫ�����˫ɫ����һ�ԣ�����һ��ҪС�ģ�");
}