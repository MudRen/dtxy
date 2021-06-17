//puti.c
inherit NPC;
inherit F_MASTER;
#include <ansi.h>
int cure_longear();
int begin_go();
int bian_yuan();
int fly_sea();
int ask_longjin();
int ask_pansi();

void create()
{
       set_name(HIW"������ʦ"NOR, ({"master puti","puti", "master"}));
       set("long", "�������û���ˣ���������������\n");
       set("title", HIC"б������"NOR);
       set("gender", "����");
       set("age", 100);
	set("class", "taoist");
       set("attitude", "friendly");
       set("shen_type", 1);
       set("rank_info/respect", "��ʦ��");
       set("per", 26);
	set("looking", "�������󣬲������Ʈ���𾦷ɻ��棬��Ŀ��ü�ҡ�");
	set("int", 30);
       set("max_kee", 5000);
       set("max_gin", 1000);
       set("max_sen", 5000);
       set("force", 5000);
       set("max_force", 2500);
       set("force_factor", 150);
       set("max_mana", 2500);
       set("mana", 5000);
       set("mana_factor", 150);
       set("combat_exp", 3000000);
	set("daoxing", 10000000);

       set_skill("literate", 180);
       set_skill("unarmed", 180);
       set_skill("dodge", 180);
       set_skill("parry", 180);
	set_skill("stick", 200);
	set_skill("sword", 180);
	set_skill("liangyi-sword", 180);
	set_skill("spells", 200);
	set_skill("dao", 180);
	set_skill("puti-zhi", 180);
	set_skill("wuxiangforce", 200);
	set_skill("force", 200);
	set_skill("qianjun-bang", 180);
	set_skill("jindouyun", 180);
	map_skill("spells", "dao");
	map_skill("unarmed", "puti-zhi");
	map_skill("force", "wuxiangforce");
	map_skill("stick", "qianjun-bang");
	map_skill("parry", "qianjun-bang");
	map_skill("dodge", "jindouyun");
	map_skill("sword", "liangyi-sword");
	set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
		(: cast_spell, "light" :),
		(: cast_spell, "dingshen" :),
                (: cast_spell, "thunder" :)
        }) );
    set("inquiry",([
    "��̨����": (: begin_go :),
    "����": (: fly_sea :),
    "��ϼ": (: ask_pansi :),
    "��ϼ": (: ask_pansi :),
    "��ϼ����": (: ask_pansi :),
    "��ϼ����": (: ask_pansi :),
    "����": (: ask_longjin :),
	"˳���": (: cure_longear :),  
	"��������": (: bian_yuan :),  
	"Ԭ�س�": (: bian_yuan :),  
]));
create_family("����ɽ���Ƕ�", 1, "��");
setup();

        carry_object("/d/lingtai/obj/pao")->wear();
        carry_object("/d/lingtai/obj/shoe")->wear();
        carry_object("/d/lingtai/obj/putibang")->wield();
}

void init()
{
        object me;
    me=this_player();

        ::init();
        
	   if (me->query("fangcun/panlong_accept")=="done")
		   return;
       if (me->query("fangcun/panlong_nowaylingtai"))
		   return;

	   if (me->query("fangcun/panlong_accept")=="begin")
	{
		call_out("panlong_accept",2,me);
		return;
	}
	   
	   
	   if ((me->query("fangcun/panlong_qiansi_finish")==1)&&(!me->query("fangcun/panlong_noway")))
		{
                
			if ((me->query("fangcun/panlong_visite")>=1) && (me->query("fangcun/panlong_visite")<11))
			{
				call_out("begin_visite2",2);
			    return;
			}
			
			if (me->query("fangcun/panlong_visite")>=11)
	      {
            command("say ͽ����������ݳ������ˣ�����Ҿ��죨�����壩�˽�һ�����\n");
			me->move("/d/wiz/outjail");
            me->save();
			 return;
		  }
				remove_call_out("greeting");
                call_out("greeting", 2, me);
        
	     return;
		 }
    
		

}

int accept_object(object me, object ob)
{
  if ((me->query("fangcun/panlong_wzg_rsg")=="done")||(me->query("fangcun/panlong_wzg")=="done"))
	{	 
	 if (ob->query("id") == "renshen guo")
	{
	 command ("nod "+me->query("id"));
      command ("say �Ǻǣ�ͽ�����������ˣ�");
      me->delete("fangcun/panlong_nowaywzg2");
      call_out("destroy", 1, ob);
      return 1;
	}
	}
return 0;
}

int begin_go()
{
	object me,ob;
    int visite;
	me=this_player();
	ob=this_object();
  
   if (me->query("fangcun/panlong_accept")=="done")
	{
        command("say " + RANK_D->query_respect(me) + "�����Ѿ�������������ʽ��������ʲô��\n");
		return 0;
	}

   if (me->query("family/family_name")!="����ɽ���Ƕ�")
      return 0;
   
  
   if (me->query("fangcun/panlong_nowaylingtai"))
	{
        command("say " + RANK_D->query_respect(me) + "�����Ѿ������һ���ˣ�����������ỹ���ø����˰ɣ�\n");
		return 0;
	}

	if (me->query("betray/count"))
   {
     me->delete("fangcun");
     command("say ͽ��������ʦ����Ͷ�ҷ���ɽ����������ʽ����ѧ����ģ�\n");
	 return 0;
   }

   if (!me->query("fangcun/panlong_visite"))
	return 0;
//   sscanf(me->query("fangcun/panlong_visite"),"%d",visite);
   

		if (me->query("fangcun/panlong_visite")<=3)
	       {
	        command("say ͽ�����������뵽�������ƺ�̫�٣�\n");
            return 1;
		   }     	
	    	
       visite=me->query("fangcun/panlong_visite");
       me->set_temp("panlong_visite",visite);
		   		
		if (me->query("fangcun/panlong_nowayshushan"))
			me->add_temp("panlong_visite",-1);
     	if (me->query("fangcun/panlong_nowayputuo"))
			me->add_temp("panlong_visite",-1);
     	if (me->query("fangcun/panlong_nowaymoon"))
			me->add_temp("panlong_visite",-1);
     	if (me->query("fangcun/panlong_nowaylonggong"))
			me->add_temp("panlong_visite",-1);
     	if (me->query("fangcun/panlong_nowayjjf"))
			me->add_temp("panlong_visite",-1);
     	if (me->query("fangcun/panlong_nowaywzg1"))
			me->add_temp("panlong_visite",-1);
        if (me->query("fangcun/panlong_nowaywzg2"))
			me->add_temp("panlong_visite",-1);
		if (me->query("fangcun/panlong_nowaywzg3"))
			me->add_temp("panlong_visite",-1);
        if (me->query("fangcun/panlong_nowaypansi"))
			me->add_temp("panlong_visite",-1);
		if (me->query("fangcun/panlong_nowayhell"))
			me->add_temp("panlong_visite",-1);
	   if (!me->query("fangcun/panlong_times"))
            me->set("fangcun/panlong_times",1);
	       else
	       {
	         me->add("fangcun/panlong_times",1);
		   }
       if (me->query_temp("panlong_visite")<=4)
	       {
     		  //me->delete("fangcun");
			  command("say ��ͽ���㻹����������\n");
	       	  me->set("fangcun/panlong_nowaylingtai",1);

            return 0;
		   }     	
		      
		
		   call_out("finish_visite",1,me);
return 1;
}

void attempt_apprentice(object ob)
{	ob=this_player();
	if( (string)ob->query("family/family_name")=="����ɽ���Ƕ�") {
	if ((int)ob->query("daoxing") < 500000 ) {
  	command("say ��������֮ʿ���صľ��ǵ��У�" + RANK_D->query_respect(ob) + "������Ŭ��������������\n");
	return;
	}
/*
	if( (int)ob->query("pending/kick_out")) {
	command("say ��λ" + RANK_D->query_respect(ob) + "�����޳����Ϸ�ԭ������Ϊͽ�ˣ�\n");
	command("sigh");
	return;
	}
*/
	if ((int)ob->query_int() < 35) {
	command("say ��λ" + RANK_D->query_respect(ob) + "����̫�ͣ�����������Ҳ������Ϊ��\n");
	command("sigh");
	return;
	}
	if( (int)ob->query_skill("dao", 1) < 120 ) {
	command("say ��λ" + RANK_D->query_respect(ob) + "���ҵ����ɷ���ỹ�������������Ҳ����Ϊ���ѣ��������գ�\n");
	command("sigh");
	return;
	}
        command("smile");
        command("say �ܺã�" + RANK_D->query_respect(ob) + "���Ŭ�������ձض��гɡ�");
        command("recruit " + ob->query("id") );
	return;
	}
        command("shake");
        command("say �Ϸ������ŵ��ӣ�" + RANK_D->query_respect(ob) + "������Ѱ���˰ɣ�\n");
        return;
}
int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "taoist");
}

int accept_fight(object me, object ob)
{	ob=this_player();
	command("say " + RANK_D->query_rude(ob) + "ɱ��̫�أ��ֻ������ѣ�\n");
	return 0;
}
void die()
{

        if( environment() ) {
        message("sound", "\n\n������ʦ΢��üͷ���������˹��Ǹ���ɵؾ͵ģ�\n\n", environment());
        command("sigh");
        message("sound", "\n������ʦ����һת�������������ˡ�����\n\n", environment());
        }

        destruct(this_object());
}

int fly_sea()
{
      object me;
    me=this_player();
	  if (me->query("fangcun/panlong_wzg")!="begin")
		  return 0;
	message_vision("\n������ʦ��ָһ�㣬Ц��������Ԫ�ϵ������ǲ�֪������Ը��������õ����أ���̰�汾���Ѹģ�
	                ��ׯ����ѵͽ���ϣ�ֻ�ü�װ��֪�������ͽ��֮��Բ��ͽ����һ��
		        ��Ը��ɵͽ������ȥ���ʰ���"+HIY"���ζ���"+NOR"֮�£����֪�����������ˣ�\n\n",me);
	me->set_temp("wzg_baxian","go");
	return 1;
}

int ask_longjin()
{
      object me;
    me=this_player();
    if ((me->query("fangcun/panlong_hell_18")=="done")&&(me->query("fangcun/panlong_hell_longjin")=="begin"))
	{
			message_vision("\n������ʦ�Ե��˵�ͷ����ͽ��������������ˣ����Ͳ��棬�����Ʊ��ӵ��Ϻò��ϣ�ֻ����ÿ������
	              ��Ҳ��һ��������Զ��������޵ظ������--��������"+NOR"�ο�������ʧ����
	              �ܴ������������������ͽ������ɽ���"+HIY"��ɱ��������Ϊ�����������
                      ɱ������������ɱ�޹���Ϊ���ɼ������ܣ�\n\n"NOR,me);
	        return 1;
	}
    return 0;
}

int ask_pansi()
{
	object me;
    me=this_player();
	if (me->query("fangcun/panlong_nowaypansi"))
	{
			message_vision("\n������ʦ���쳤̾һ����������ϼ����ϼԭ�������������������ϲ�����һ���������о������������ϣ�
			˽���½��һֱ�໥�������µ����Ҳ��������ˣ���������������\n\n",me);
    		command ("sigh " + me->query("id"));
			return 1;
	}
	if (me->query("fangcun/panlong_pansi")=="done")
	{
			message_vision("\n������ʦ΢Ц�ŵ�ͷ��������ϼ����ϼԭ�������������������ϲ�����һ���������о������������ϣ�
                      ˽���½��һֱ�໥������ͽ���������ջ��������ö���ǧ��Թ�ޣ�ʹ�����
                      ��������ҷ�ʵ�˹�������������Ϊ�˵����콫Ҳ����̫�������ϣ�������
                      ����С�ڣ���˲ź�Ϊʦ�����ӡ�\n\n",me);
    		command ("haha ");
			return 1;
	}
	return 0;
}

int cure_longear()
{
      object me;
    me=this_player();
	  if (!me->query_temp("putuo/longear"))
		  return 0;

		command ("haha " + me->query("id"));
		call_out("cure_longear1",3);
		return 1;
}

void cure_longear1()
{
   	object me;
    me=this_player();

	message_vision("\n������ʦ������Ц����ɵͽ����������˳�����ë���ַ��ˣ����к��ѣ�"+HIY"��β��"+NOR+""+"����������"+HIY"ţ��
	            "+NOR""+"֮���ⶾ�������������ʹ��"+HIY"�Ͼ�"+NOR""+"��Ѫ���׸���"+HIY"��Ƥ"+NOR""+"˳����̵֮��Ч��
                    �Ҷ�����ҩ��������\n",me);
}

int bian_yuan()
{
	object me;
    me=this_player();
	  if (me->query_temp("fangcun/panlong_longgong_yuanshoucheng")!="begin")
		  return 0;
    command ("hmm " + me->query("id"));
	call_out("bian_yuan1",3);
    return 1;
}

void bian_yuan1()
{
   	object me;
    me=this_player();
	message_vision("\n������ʦ������˼����ͽ�������¶��³����򣬶�������˵������������ݺ���������
                    ������۽�ּն֮�����ȥ�ʹ�����������"+HIY"��������"+NOR"֮�£�����
	            ���˵������а�����������е����ҵ�����ּ�����в���������
	            �ϣ����˺��ˣ�\n\n",me);
}

void greeting(object ob)
{
        command ("nod " + ob->query("id"));
		if( !ob || !visible(ob) || environment(ob) != environment() ) return;
                message_vision("\n\n"NOR,ob);
				command ("say " + "��ͽ��,����ʦ����������ǧ��������ѧ[������ʽ]�Ժ�ǧ����,����̨
              ����ɽ��һ�����ܲ����,���յü���"+ob->query("name")+"ͽ���������֮��,��������
              ����ɽ�ĸ��֣����������ܵ�����ͽ��,����Ҳ���������ѣ�\n\n" );
	call_out("begin_visite", 1, ob);
}

void begin_visite(object me)
{
command("say " + me->query("name") + ",��������[������ʽ]���ҷ���ɽǧ�������е��ռ�����,����С����
              ����Ϊ����,�����ɷ�Ϊ����,�����ս�����������ڰ�����,һ��������
              ����,��������.�����պ����д��컯ѧ��[������ʽ]Ҳ��Ҫ���ǽ�����ħ
              ,�����е�,�������²���������֮����\n\n");
     call_out("begin_visite1", 1, me);
}

void begin_visite1(object me)
{
	 
      command("say ���������·ȥ�����λ�ɼҵ�����ǰ���ҡ���̨����,��ʱ�ҵ��ڴ�
	      ����[������ʽ],�����ܷ��������а����ȫ�����Ե����,ȥ��,ȥ�ɣ�\n");
      me->set("fangcun/panlong_visite",1);
}

void begin_visite2()
{
	command("say ��ͽ����������ʲô�Ѵ���");
}

void finish_visite(object ob)
{
   command("smile");
   command("say ��ͽ��,���鶼������,���ϵ���Ժ��.");
   message_vision(HIW"\n������ʦ˵��Ͳ����ˣ�\n"NOR,ob);
   this_object()->move("/d/lingtai/inside1");
  // ob->delete("fangcun/panlong_visite");
   ob->set("fangcun/panlong_accept","begin");
   ob->delete("fangcun/panlong_qiansi");
}

void panlong_accept(object me)
{
 int pass;
 me->delete_temp("panlong_nopass");
 me->delete_temp("master");
 me->delete_temp("take_panlong");
 if ((present("bai mei"))&&(!userp(present("bai mei"))))
    {
	 me->add_temp("take_panlong",1);
	 me->set_temp("master/shushan","come");
	}
if ((present("xi wangmu"))&&(!userp(present("xi wangmu"))))
    {
	 me->add_temp("take_panlong",1);
	 me->set_temp("master/moon","come");
	}
if ((present("lao ren"))&&(!userp(present("lao ren"))))
    {
	 me->add_temp("take_panlong",1);
	 me->set_temp("master/jjf","come");
	}
if ((present("guanyin pusa"))&&(!userp(present("guanyin pusa"))))
    {
	 me->add_temp("take_panlong",1);
	 me->set_temp("master/putuo","come");
	}
if ((present("ao guang"))&&(!userp(present("ao guang"))))
    {
	 me->add_temp("take_panlong",1);
	 me->set_temp("master/longgong","come");
	}
if ((present("zhenyuan daxian"))&&(!userp(present("zhenyuan daxian"))))
    {
	 me->add_temp("take_panlong",1);
	 me->set_temp("master/wzg","come");
	}
if ((present("dizang pusa"))&&(!userp(present("dizang pusa"))))
    {
	 me->add_temp("take_panlong",1);
	 me->set_temp("master/hell","come");
	}
if (!me->query("fangcun/panlong_nowaywzg3"))
	 me->add_temp("take_panlong",1);
if (!me->query("fangcun/panlong_nowaywzg2"))
	 me->add_temp("take_panlong",1);
if (!me->query("fangcun/panlong_nowaywzg1"))
	 me->add_temp("take_panlong",1);
if (!me->query("fangcun/panlong_nowayshushan"))
	 me->add_temp("take_panlong",1);
if (!me->query("fangcun/panlong_nowaylonggong"))
	 me->add_temp("take_panlong",1);
if (!me->query("fangcun/panlong_nowaypansi"))
	 me->add_temp("take_panlong",1);
if (!me->query("fangcun/panlong_nowayhell"))
	 me->add_temp("take_panlong",1);
if (!me->query("fangcun/panlong_nowayputuo"))
	 me->add_temp("take_panlong",1);
if (!me->query("fangcun/panlong_nowaymoon"))
	 me->add_temp("take_panlong",1);


pass=random(me->query_temp("take_panlong")) + random( me->query("lunhui_zhuanshi") );
if (pass<=10)
	me->set_temp("panlong_nopass",1);
me->set_temp("pass/total",me->query_temp("take_panlong"));                          // waring del
me->set_temp("pass/random",pass);                          // waring del
 message("chat",HIC+"��"+HIW+"��������"+HIC+"��������ʦ(Master puti)����ͽ��"+me->query("name")+"���������Ҫ�����������λ�ɼҵ���ͬ����̨����\n\n"NOR,users());
message_vision(HIC"\n���˶���������ʦ��ȭ����\n\n"NOR,me);

message_vision(HIC"\n������ʦת��������$N������ͽ����������ʽּ���򣬶�����ѧ����ע�⿴���ˣ�\n"NOR,me);
call_out("direct_panlong",5,me);
}

void direct_panlong(object me)
{
	message_vision(HIY"\n������ʦһ�����������ȣ���Ȼ��һ�ɾ�����������ʦ�ĵ�������ӿ�����\n"NOR,me);
    message_vision(HIY"\n\n������ʦ��ʱ����һ�Ž�⣬����ǧ�������������鶯������ɱ������Ȼ��һ����Х�����������\n"NOR,me);
	message_vision(HIY"\n\nХ������������ʦ��ʹ�����ȵ��ʯ�����������У��ǽ����ơ��������׺���̤��Х���족��
	����֮������ɲʱ��Ժ����Ҷ��ȥ��ʯ��ʯ���������������������С�飬$N����������
        ��Ҳ�������������ˣ�\n"NOR,me);
    me->set("eff_kee",(me->query("eff_kee"))/20);
	me->set("kee",(me->query("kee"))/10);
	me->set("eff_sen",(me->query("eff_sen"))/20);
	me->set("sen",(me->query("sen"))/10);
    message_vision(HIY"\n������ʦ��ס��ʽ�����ɼҾ���̾�кã�\n"NOR,me);
	message_vision(HIR"\n\n$N�������ˣ�֧�ֲ�ס��һ���������ڵأ�\n"NOR,me);
	message_vision(HIC"\n������ʦ�ߵ�$N��ǰ��������ͽ������ú����һ�£������������ʲô����\n"NOR,me);
	call_out("direct_panlong1",10,me);
}

void direct_panlong1(object me)
{
	   message_vision(HIC"\n\n\n������ʦ���ֱ�ȭ�Ը������ŵ��������������񵽴�Ϊֹ����λԶ���������뵽ƶ��ɽ��һ�Σ�Ҳ��ƶ��һ������֮�ˣ�\n"NOR,me);
   if (me->query_temp("master/shushan"))
	{
            message_vision(HIC"\n��ü(Bai mei)���ø�����������֮�Ե������¾�����һ�ܼ���\n"NOR,me);
        destruct(present("bai mei"));
	}
   if (me->query_temp("master/moon"))
	   {
          message_vision(HIC"\n����ĸ(Xi wangmu)�����겻���������ʦ��Ȼ���粻�����꣬���˺��������\n"NOR,me);
          message_vision(HIC"������ʦ(Master puti)����ĸ��������ˣ�\n"NOR,me);
		  destruct(present("xi wangmu"));
		}
   if (me->query_temp("master/jjf"))
	{   
       message_vision(HIC"\n�׷�����(Lao ren)���������ټ������ʦ��������ʽ�����ǲ�������ѽ��\n"NOR,me);
	   destruct(present("lao ren"));
	}
   if (me->query_temp("master/putuo"))
	{
	   message_vision(HIC"\n��������(Guanyin pusa)���ѹ��Ǻ���һ������𹿰������칬֮ʱ��һ���������콫�����ܵ���\n"NOR,me);
	   destruct(present("guanyin pusa"));
	}
   if (me->query_temp("master/longgong"))
	{
	   message_vision(HIC"\n����(Ao guang)���Ƕ������������������������������������ҿ�����ôһֻ���ӣ�\n"NOR,me);
	   destruct(present("ao guang"));
	}
   if (me->query_temp("master/wzg"))
	{
	   message_vision(HIC"\n��Ԫ����(zhenyuan daxian)���������������ǽ���ֵܱ��¿ɲ�Сѽ��\n"NOR,me);
	   destruct(present("zhenyuan daxian"));
	}
	if (me->query_temp("master/hell"))
	{
	   message_vision(HIC"\n�ز�������(Dizang pusa)����̨��������Ӣ�۱��������������ˣ�\n"NOR,me);
	   destruct(present("dizang pusa"));
	}
       message("chat",HIC+"\n\n��"+HIY+"��������"+HIC+"��������ʦ������Ц�˼�����\n"NOR,users());
	message_vision(HIC"\n������ʦ(Master puti)����λ���ѣ��������Ҳ������ͷ���ϵ����ͷǰ��·����ҿ����ҷ���ɽ�ľ�����Σ�\n"NOR,me);
	message_vision(HIY"\n����һͬ��Ȼ��ȭ�����룮\n"NOR,me);
   message_vision("\n\n$N�����ڵصȺ�ʦ��ʾ�£�ͻȻ�������ᴫ��������ʦ��������\n"NOR,me);
   message_vision(HIR"\nͽ�����Ҵ������뿪�������㵽С�Ҿ���Ǳ˼���ܷ�����"+HIY"������ʽ "+HIR"���ڴ�һ�٣�\n"NOR,me);
   message_vision(HIB"\n$N���ȱ�Ŀ�����Ļ���ղ�ʦ����ʹ��"+HIY"������ʽ"+NOR"��\n",me);
   me->start_busy(20);
   me->move("/d/lingtai/lou");
	call_out("direct_panlong2",15,me);
}

void direct_panlong2(object me)
{
   if (!me->query_temp("panlong_nopass"))
	{
	   message_vision(HIR"\n\n\n    $NǱ˼���գ�ͻ�������������������Լ�������һƬ�յ��ֳ�"+HIY"�𹿰�"+HIR"����ͣЪ��ʹ����
����ʽ��ֱ�����������£�����$N�����۾��������纣Х����ǰ���ƽ��������������"+HIY"����"+HIR"������\n"NOR,me);
message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"��ĳ�ˣ�"+ me->name()+"ͨ����̨�����飬����������"+HIY"����"+HIR"������\n"NOR,users());
	  // me->delete("fangcun");
	   me->set("fangcun/panlong_accept","done");
	   me->set("fangcun/panlong_qiansi_finish",1);
       present("master puti")->move("/d/lingtai/room");
	   return;
	}
   message_vision(HIR"\n\n\n$NǱ˼���գ�ͷ����һƬ���ң�ֻ��ϡ��סʦ����ʹ�ĵ���ʽ���ղ��ܻ�Ϊ���ã�\n"NOR,me);
   message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"��ĳ�ˣ�"+ me->name()+"��Ȼͨ����̨�����飬��ϧԵ��δ�����ղ���������"+HIY"����"+HIR"������\n"NOR,users());
   present("master puti")->move("/d/lingtai/room");
   me->delete("fangcun/panlong_accept");
   if (me->query("fangcun/panlong_times"))
   {
	   //me->delete("fangcun");
	   me->set("fangcun/panlong_qiansi_finish",1);
       me->set("fangcun/panlong_nowaylingtai",1);
   }
}

void destroy(object ob)
{
  destruct(ob);
}

�
