// �����硤���μǡ��汾��������
/* <SecCrypt CPL V3R05> */
 
//change.c
inherit NPC;
#include <ansi.h>
inherit F_MASTER;
string ask_sanshou();
string ask_jueqing();
int do_lianxi();
void create()
{
       set_name("�����ɹ�",({"chi meng","dream", "fairy"}));
       set("long",
"�����Խ�����ɹ�Ҳ�����ܽ���֮л��������Ե�߶�֮��\n");
       set("title", "�Խ����");
       set("gender", "Ů��");
       set("age", 18);
       set("class", "xian");
       set("attitude", "friendly");
       set("rank_info/respect", "�ɹ�");
       set("per", 30);
   set("int", 30);
       set("max_kee", 1000);
       set("max_gin", 1000);
       set("max_sen", 1000);
       set("force", 800);
       set("max_force", 800);
       set("force_factor", 50);
       set("max_mana", 500);
       set("mana", 500);
       set("mana_factor", 40);
       set("combat_exp", 1000000);

        set("eff_dx", 100000);
        set("nkgain", 300);

       set_skill("literate", 90);
       set_skill("parry", 100);
       set_skill("unarmed", 80);
       set_skill("dodge", 100);
       set_skill("force", 120);
       set_skill("whip", 180);
       set_skill("unarmed", 80);
       set_skill("spells", 120);
       set_skill("baihua-zhang", 120);
        set_skill("moonshentong",140);
        set_skill("jueqingbian", 180);
        set_skill("moonforce", 120);
        set_skill("moondance", 100);
        map_skill("spells", "moonshentong");
        map_skill("unarmed", "baihua-zhang");
        map_skill("force", "moonforce");
        map_skill("whip", "jueqingbian");
        map_skill("parry", "jueqingbian");
        map_skill("dodge", "moondance");
        set("inquiry",([
      "����": (: ask_jueqing :),
      ]));


create_family("�¹�", 2, "����");
setup();

       // carry_object("/d/obj/book/lovebook");
        carry_object("/d/obj/cloth/luoyi")->wear();
   carry_object("/d/obj/weapon/whip/jueqingwhip")->wield();
}

void init()
{
        add_action("do_lianxi", "lianxi");
}

string ask_sanshou()
{
    object me=this_player();

    if(me->query("family/family_name") != "�¹�" )
                return ("�㲻�����¹�����!!\n");
    if(me->query("faith")<500)
       return ("��Ա������˶��ٹ��ף�����������������֣�");
    if( (string)me->query("gender") !="Ů��")
                return ("���Ϊ����֮��,����֪��Ů���ҵ���˼??\n");
//    if(me->query("family/master_id") != "chi meng")
//     return ("�㲻���ҵĵ���,������\n");
    if(me->query("JQB_known"))
      return ("�㲻���Ѿ�֪����ô���ѵ�����ϷŪ�ҵģ�");
    command("pat "+me->query("id"));
    me->set("JQB_known",1);
    return ("�㸽��������������������������...");
}
string ask_jueqing()
{
	object me=this_player();
	if(me->query("family/family_name") != "�¹�" )
                return ("�㲻�����¹�����!!\n");
        if( me->query("betray/count") )
		return ("�����Ķ����޷�����¹���ѧ��\n");
        if( (string)me->query("gender") !="Ů��")
                return ("���Ϊ����֮��,����֪��Ů���ҵ���˼??\n");
        if(me->query("jueqing_known"))
      		return ("�����о���޵Ŀھ��㶼�Ѿ�֪���˰���");
      	if(me->query("jueqing_cant"))
      		return ("���������Ե��");
      	if(me->query("jueqing/chimeng"))
      		return ("�����о���޵Ŀھ��㶼�Ѿ�֪���˰���");
      	if( !me->query_temp("jueqing/chimeng") )
      	{
      		me->set_temp("jueqing/chimeng",1);
      		command("sigh");
	      	command("say ��������Ϊ���ֱ������������");
	      	command("say ��ô�����ȥ�ˣ��ѵ�ʦ�û���û�п����𣿣�");
	      	return("���¹������е���ź�����ر���ͨ���ϣ���������Ұ�ʦ����(dig)һ���ɣ�");
	}
	else if( me->query_temp("jueqing/chimeng") == 2 )
	{
		return("�ã����Ȼ���ġ����Ȱ�����ź�����϶�ʦ�ã������ұ㴫�����޵Ŀھ���");
	}
	else if( me->query_temp("jueqing/chimeng") == 3 )
	{
		me->set_temp("jueqing/chimeng",4);
		return("�ã��鵽������������ܻ�����ָ�ᡣ��������Ծ���Ϊ����ʵ������֮�����������ϰ��lianxi��һ�°ɣ����Ի���һ��ָ�����㣡");
	}
      	else if( me->query_temp("jueqing/chimeng") == 4 )
      	{
      		return("�㻹�ǿ����ϰ�ɣ�");
      	}
      	else
      	{
      		return("��ȥ������(dig)��ź�ɣ�");
      	}
}
void attempt_apprentice(object ob)
{
        if ( !((string)ob->query("gender")=="Ů��")){
           command("shake");
           command("say �����¹�ֻ��Ůͽ����λ" +
   RANK_D->query_respect(ob) + "��������߾Ͱɡ�\n");
           return ;
        }
//if (random(this_player()->query_kar()) < 3 || this_player()->query("mark/moon_chimeng")){
//     this_player()->set("mark/moon_chimeng", 1);
//     command("shake");
//     command("say ������Ե����������߾Ͱɡ�\n");
//     return ;
//   }
        else{
   command("pat "+ob->query("id"));
        command("say ��Ȼ" + RANK_D->query_respect(ob) +
"������Ե���Ҿ��������ˡ�\n");
        command("recruit " + ob->query("id") );
        return ;
}
}
int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "xian");
     ob->set("title", HIM"�����ɹ��״�����"NOR);
}

int do_lianxi()
{
	object me=this_player();
	object weapon = me->query_temp("weapon");
	if( me->query_temp("jueqing/chimeng") != 4 )
		return 0;
	if( me->query_temp("lianxi") )
		return notify_fail("��������ϰ��\n");
	if( me->is_busy() )
		return notify_fail("������æ���أ�\n");
	 if (!objectp(weapon)
                || (string)weapon->query("skill_type") != "whip")
                        return notify_fail("û�б�����ô��ϰ����ޣ�\n");
	me->set_temp("lianxi",1);
	me->set_temp("no_move",1);
	me->start_busy(10);
	message("vision", "��Ĭ������ɹô��ڵĿھ�����ʼ��ϰ����ޡ�\n", environment());
	call_out("check",2,me,1);
	return 1;
}

int check( object me,int kk)
{
	if( !me )	
		return 1;
	if( environment(me) != environment(this_object()) )
	{
		tell_object(me,"���뿪�˺��ߣ�ʧȥ�˳��ε�ָ�㣬�޷�������ϰ������ˣ�");
		me->delete_temp("lianxi");
		return 1;
	}
	if( !me->is_busy() )
		me->start_busy(3);
	remove_call_out("check");
	if( kk < 8 ) 
		call_out("check",2,me,kk+1);
	else
	{
		me->delete_temp("no_move");
		me->set("jueqing/chimeng",1);
                me->delete_temp("lianxi");
                me->delete_temp("jueqing/chimeng");	
	}
	switch (kk)
        {
        	case 1:
                { 
                      	message_vision("$N������ת������ᶶ��ʹ��һʽ"HIM"�����˫�ɡ�"NOR"��\n",me);
                        break;
                }
                case 2:
                { 
                      	message_vision("$N���һʽ"HIM"����Ӧ���"NOR"����ɫ����Ȼ��\n",me);
                        break;
                }
                case 3:
                { 
                      	tell_object(me,"\n\n���ߴ������ε��������ã��������ȣ���Ȼ���Թ��ˡ�\n\n");
                      	message_vision("$N��ͷ������ת��ʹ��"HIM"��������ơ�"NOR"���������������\n",me);
                        break;
                }
                case 4:
                { 
                      	message_vision("ֻ��$Nһ·"HIM"����į��ġ�"NOR"��ʹ�ûط���ѩ��������������˿��֮�������������ĳ��������ʱ����ʤ������\n",me);
                        break;
                }
                case 5:
                { 
                      	tell_object(me,"\n\n���ߴ������ε����������´�������ǧ����ţ������Ĳ��䣬���಻�䡣\n\n");
                      	message_vision("��Ȼ��$N���ƶ��䣬���ٴ죬���ⰻȻ��һʽ"HIM"��ǧ����š�"NOR"����֮�����֮�����ǧ�����໯����һ��֮�С�\n",me);
                        break;
                }
                case 6:
                { 
                	tell_object(me,"\n\n���ߴ������ε�����������޵ľ��辡��һ�����֣���Ҫ֪�����Ⱦ�Ҫ���顣\n\n");
                      	message_vision("$N�������һ�У�����������繲��࣬�������ߣ�����˫˿��������ǧǧ�ᣬֱ�Ǽ�֮���ϣ���֮���ҡ�\n",me);
                        break;
                }
                case 7:
                { 
                      	message_vision("$N�����������ڱ��˺�һ�����"HIM"����������"NOR"��ֻ��$N����ʱ���������죬���䴦������ϼǧ�ơ�\n",me);
                        break;
                }
                case 8:
                { 
                      	tell_object(me,"\n\n����˵�����ã��á���ô�̵�ʱ������������޵ľ��裬��Ҳûʲô�ý�����ˣ����ȥ���϶�ʦ�ðɣ�\n\n");
                      	message_vision("\n$Nͣ����ϰ������һ����ֻ����߲к����أ���������һ�Ժ�Ц����$N��\n",me);
                        break;
                }
	}
	return 1;
}
