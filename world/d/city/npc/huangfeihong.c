// by gslxz@mhsj 1/7/2001
#include <ansi.h>
inherit NPC;
int check_name(string str,object me);
int create_banghui(string str);
void create()
{
        set_name("����", ({ "tu di", "tudi" }) );
        set("long",
                "�������أ�ר�Ÿ�����ư������\n");
	set("title", HIW"��������"NOR);
        set("attitude", "heroism");
       
        set("str", 27);
        set("cor", 26);
        set("cps", 25);
	set("agi",55);
	set("int",30);
        set("chat_chance_combat", 50);
        set("chat_msg_combat", ({
                (: perform_action, "unarmed.yuhuan" :),
        }) );
        set("inquiry", ([
		"banghui"	:"Ҫ���������create <�����>\n",
		"���"		:"Ҫ���������create <�����>\n",
        ]) );
        set("combat_exp", 9000000000);
	set_temp("apply/damage",500);
        set_skill("unarmed", 1000);
	set_skill("sword",1000);
	set_skill("force",1000);
        set_skill("parry", 1000);
        set_skill("dodge", 1000);
	set_skill("changquan",1000);
	set_skill("literate",1000);
	
   map_skill("unarmed","changquan");
	        setup();

}
void attempt_apprentice(object me)
{
	command("sigh");
	command("say �Һεº��ܣ�\n");
}
int check_name(string name,object me)
{
        int i;

        i = strlen(name);

	if( (strlen(name) < 4) || (strlen(name) > 16 ) ) {
		tell_object(me,"��������붨�ڶ����˸��֡�\n");
                return 0;
        }
        while(i--) {
                if( name[i]<=' ' ) {
			tell_object(me,"�Բ�����İ�����в����ÿ����ַ���\n");
                        return 0;
                }
                if( i%2==0 && !is_chinese(name[i..<0]) ) {
			tell_object(me,"���á����ġ�������İ�ᡣ\n");
                        return 0;
                }
        }
	return 1;
}

// by gslxz@mhsj 1/7/2001

void init()
{
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() )
                {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
                }
	add_action("create_banghui","create");
}
void greeting(object ob)
{
	string banghui;
	object lingpai;
	if( !ob || environment(ob) != environment() ) return;
	if((string)(banghui=ob->query("banghui")))      {
		lingpai=new("/obj/lingpai");
		lingpai->create(banghui);
		if(lingpai->query("no_use"))	{
			tell_object(ob,"���ص���"+ob->query("name")+"����İ���ļ������⣬������ʦ��ϵ�ɡ�\n");
		}
		else if(lingpai->query("bangzhu_id")!="???")	{
			if( lingpai->query("bangzhu_id")==ob->query("id") &&
			lingpai->query("bangzhu")==ob->query("name"))
			tell_object(ob,"����һ��ȭ������λ"+ob->query("banghui")+
			ob->query("bh_rank")+"�����������Σ�\n");
			else	tell_object(ob,"���ص���"+ob->query("name")+
			"������������ɺã�\n");
		}
		else tell_object(ob,"����͵͵������ߵ��������ʧ�ٶ��գ�"+
                        RANK_D->query_respect(ob)+"ֻ�軨һǧ���ƽ�Ϳ������°���֮λ��\n");
		destruct(lingpai);
	}
	else	tell_object(ob,"���ض���һ��ȭ������λ"+RANK_D->query_respect(ob)+"��������������<create ���>��\n");
}
int accept_object(object who,object obj)
{
	string banghui;
	object lingpai;
	if(! banghui=who->query("banghui"))	{
		tell_object(who,"����Ц�����ҿɲ���ƽ���޹ʽ�����Ķ�����\n");
		return 0;
	}
	lingpai=new("/obj/lingpai");
	lingpai->create(banghui);
	if(lingpai->query("no_use"))	{
		tell_object(who,"����̾����"+who->query("name")+"����İ���ļ������⣬������ʦ��ϵ�ɡ�\n");
		destruct(lingpai);
		return 0;
	}
	if(lingpai->query("bangzhu_id") != "???")	{
		tell_object(who,"����ʮ�־��ȣ�˵��������������ĺúõģ��ҿɲ��İѰ���֮λ����"+
		RANK_D->query_respect(who)+"����\n");
		destruct(lingpai);
		return 0;
	}
	if(! obj->query("money_id"))	{
		tell_object(who,"������ü������Щ������û��Ȥ��\n");
		destruct(lingpai);
		return 0;
	}
	if(obj->value()<10000000)	{
                 tell_object(who,"���ص�������һǧ���ƽ𣬲�Ȼ����������潻����\n");
		destruct(lingpai);
		return 0;
	}
	lingpai->set("bangzhu",who->query("name"));
	lingpai->set("bangzhu_id",who->query("id"));
	lingpai->save();
	destruct(lingpai);
         this_player()->set("title",YEL+this_player()->query("banghui")+"����"NOR);
	command("chat "+who->query("name")+
"����һǧ���ƽ�������"+banghui+"����֮λ��\n");
	return 1;
}
// by gslxz@mhsj 1/7/2001
int create_banghui(string str)
{
	object me,lingpai;
	int count;

	me=this_player();
	if((string)me->query("banghui"))	{
		tell_object(me,"���Ѿ���"+me->query("banghui")+"�����ˣ���������ᡣ\n");
		return 1;
	}
	if(me->query("combat_exp")<3000000)	{
		tell_object(me,RANK_D->query_respect(me)+"��ʵս���黹��"+
		(string)(3000000-me->query("combat_exp"))+"�㣬��ʱ�޷��������ᡣ\n");
		return 1;
	}
	if(! count=me->query("oldsix/have_create"))	count=0;
	if(count>=2)	{
		tell_object(me,"����ŭ��������Ϊ����Ǵ����������ٽ���ᣬ�±��Ӱɣ���\n",);
		return 1;
	}
	
	if(! str)	{
		tell_object(me,"��Ҫ����ʲô���ֵİ�᣿\n");
		return 1;
	}
	if(! check_name(str,me)	)	return 1;

	if(file_size("/data/guild/"+str+".o")!=-1) {
		tell_object(me,"�ǳ���Ǹ������İ����������ˡ�\n");
		return 1;
	}
	lingpai=new("/obj/lingpai");
	lingpai->create(str);
	lingpai->set("bangzhu",me->query("name"));
	lingpai->set("bangzhu_id",me->query("id"));
	lingpai->set("player",([me->query("id"):me->query("name")]));
	lingpai->set("npc",([]));
	lingpai->set("area",([]));
	lingpai->set("money",0);
	lingpai->save();
	destruct(lingpai);

	me->set("banghui",str);
	me->set("bh_rank","����");
       me->set("title",YEL+me->query("banghui")+"����"NOR);
            count++;
	me->set("oldsix/have_create",count);
            me->save();
       	command("chat ��ϲ"+me->query("name")+"�İ�ᡸ"WHT+str+HIC"�������ɹ���\n");
	return 1;
}
