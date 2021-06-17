//created by greenwc
inherit NPC;
inherit F_MASTER;

#include <ansi.h>
void create()
{
  set_name("��������", ({"rulai fo", "rulai", "fo"}));
  set("long", "��ȴ���ɽ������ɲ������Ӱ�٤��������ү��\n");
//�˲�����������
//LONG);
set("title", "������Ӱ�٤��");
  set("gender", "����");
  set("age", 400);
  set("str", 40);
  set("per", 40);
  set("int", 30);
  set("cor", 50);
  set("cps", 40);
       set_skill("literate", 300);
        set_skill("spells", 300);
        set_skill("buddhism", 300);
        set_skill("unarmed", 300);
        set_skill("jienan-zhi", 300);
        set_skill("dodge", 300);
        set_skill("lotusmove", 300);
        set_skill("parry", 300);
        set_skill("force", 300);
        set_skill("lotusforce", 300);
        set_skill("staff", 300);
        set_skill("lunhui-zhang", 300);
	map_skill("spells", "buddhism");
	map_skill("unarmed", "jienan-zhi");
	map_skill("dodge", "lotusmove");
	map_skill("force", "lotusforce");
        map_skill("parry", "lunhui-zhang");
        map_skill("staff", "lunhui-zhang");
        set("chat_chance_combat", 90);
	set("chat_msg_combat", ({
		(: cast_spell, "bighammer" :),
                        (: perform_action, "staff", "pudu" :),
                        (: perform_action, "staff", "chaodu" :),
	}) );
           set("max_kee", 5000);
	set("max_gin", 5000);
	set("max_sen", 5000);
        set("force", 40000);
        set("max_force", 20000);
        set("force_factor", 1000);
        set("max_mana", 30000);
        set("mana", 60000);
        set("mana_factor", 1500);
        set("combat_exp", 20000000);
	set("daoxing", 10000000);

        create_family("�Ϻ�����ɽ", 1, "����");
  setup();

        carry_object("/d/nanhai/obj/nine-ring")->wield();
  carry_object("/d/obj/cloth/jia_sha")->wear();
}
void init()
{
        object ob = this_player();
        remove_call_out("check");
        call_out("check",1,ob);
}

int accept_fight(object me)
{
  command("say ʩ����Ц��\n");
return 0;
}

int attempt_apprentice(object ob)
{
	string myname=RANK_D->query_respect(ob);
            if (!((string)ob->query("bonze/class") =="bonze" )) {
		command("say �ҷ�����ͨ���" + RANK_D->query_respect(ob) + "�����������������š�\n");
return 0;
}
if (((int)ob->query_skill("buddhism", 1) < 100 )) {
      command("say ʩ���Է𷨵��о����������");
return 0;
}
if (ob->query("obstacle/number") < 26) {
        command("say ��λ" + RANK_D->query_respect(ob) + "�㻹���ȳ�ȥ����һ���ɣ�\n");
        command("sigh");
        return 0;
        }
	command("pat " + ob->query("id") );
	command("say �ã�������ҷ��ŵĺõ��ӡ�ֻҪ���Ŭ�����������������\n");
	command("recruit " + ob->query("id") );
ob->set("title", HIY"�ȹ��նɷ���"NOR);
        return 1; 
}

void die()
{
        if( environment() ) {
        message("sound", "\n\n��������ҡͷ̾����ԩ��������ԩ����n\n", environment());
        command("sigh");
        message("sound", "\n������������ƣ��ǲ�����������ȥ�ˡ�����\n\n", environment());
}

	destruct(this_object());
}

void check(object ob)
{
        object mo;
        if(!objectp(ob))
        	return;
        if(ob->query("family/family_name") != "�Ϻ�����ɽ")
           	return;
        if(!userp(ob))
           	return;
        if( ob->query("fmtd_cant") )
           	return;   
        if( !ob->query_temp("fmtd/canwu") )
           	return;
        if( ob->query_temp("fmtd/canwu") == 1 )
        {
        	command("say ������Ȼ�����򵽷�ħ�ı��ʡ�");
		command("say �Է�̴����������ڷ��ն���������ħ����������������󻹲�֪������Ϊħ��");
		command("say ���ú��������˸��ǽ�������ʽ�ر���书����Ϊħ����������ϰ�ߣ��Թ�Ϊħ�ࡣ");
		command("say �˴���Ҳ���ٺ�����ϰ��Щ�������ˣ����ڲ������˽��գ�������Ϊƫ������������ħ����");
		command("say ��Ҫ�ն�������ȴ��һ�����˱���ħ�������Ƿ���Υ���˳��ԣ�");
		command("say ��ʱ���������ϣ���������һ�ˣ�����ȥ�ɻ��������������Ҵ����������Է���");
		ob->set_temp("fmtd/canwu",2);
		mo = new("/d/southern/emei/npc/mo");
		mo->copy_status(mo,ob,10);
		mo->move("/d/southern/emei/sheshenyan");
		return;
        }
        else if( ob->query_temp("fmtd/canwu") == 2 )
        {
        	command("say �����书��ǿ����ҪС�ġ�");
        	return;
        }
        else
        {
		command("say �ܺã�������ͨ�����¶Է�ħ�����Ҳ���������ˣ�����ʹ����������Է���");
		message_vision(HIC"$N����һ�ţ�������������������β��������ͣת���������������\n"NOR,this_object());
		command("say �������Ը������ã������໥������ϢϢ��ͨ��������������԰��ղ�ͬ�Ĵ����������в�ͬ��Ч����");
		message_vision(HIC"$n����$N���ϵ����ԣ�����$N�ķ�����ȫ����������𶯣���������\n"NOR,this_object(),ob);
		message_vision(HIC"$n��ǰһ�����ƺ�������һ����ȫİ���ľ��硣\n"NOR,this_object(),ob);
		ob->start_busy(15);
		if( random(ob->query("int")) > 30 - random( ob->query("lunhui_zhuanshi") ) )
			call_out("finish1",10,ob);
		else
			call_out("finish2",10,ob);
		return;
        }
        return;
}
void finish1( object me )
{
	message_vision(HIC"$N������Щ�����ݷ�ͱ�������ϢϢ��ͨ�����Դ�����ͬ�ľ����𶯡�\n" NOR,me);
	message_vision(HIC"$N�����𽥿�������ϲ���ǣ����Լ���������������˳�����\n" NOR,me);
	message_vision(HIC"$N���������Ѿ�����ϲ���ǵľ�����ʱ��ɢ��ȥ��\n" NOR,me);
	me->delete_temp("fmtd");
	me->add("fmtd_known",1);
	message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"����������(rulai fo)��" + me->name() + "�ɻ����ˣ�������"+HIB"[��ħͬ��]"+HIC"��ѧ����߾��磡\n\n\n"NOR,users());
	command("say �պ�����ƾ٣��ɻ�����������");
	return ;
}

void finish2( object me )
{
	message_vision(HIC"$N������Щ�����ݷ�ͱ�������ϢϢ��ͨ�����Դ�����ͬ�ľ����𶯡�\n" NOR,me);
	message_vision(HIC"$NŬ����ȥ��������֮���������ϵ��ȴֻ�������ݺύ��\n" NOR,me);
	message_vision(HIC"$N�����������������Ĵ���ͻ�������쳣��$Nһ�´������о��ѣ�\n" NOR,me);
	me->delete_temp("fmtd");
	me->set("fmtd_cant",1);
	message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"����������(rulai fo)��" + me->name() + "�Է𷨶ɻ����ˣ�ȴ��Ե"+HIB"[��ħͬ��]"+HIC"��ѧ����߾��磡\n\n\n"NOR,users());
	command("sigh " + me->query("id"));
	command("say �����Բ��㣬ĪҪǿ�󣬷����书������㹻��ѧ���ˣ�");
	return ;
}