//file		: PkGame.c
//purpose 	: ���˴��������ļ�(��can�Ҹĳ�CS ������)
//created	: 02-1-17 9:34
//by 		: Canoe@DHXY-Online

//history	: 02-1-17 9:34 Canoe �����ļ�

// ���� ������(canoe) PkGameԴ�����дcsϵͳ by take 02-1-30 15:41

inherit F_DBASE;
#include <ansi.h>

void over();
void ToOver();
void sort();
void check_player();
int present_users(object me);


int PK_Start = 0 ,TWin = 0 ,CtWin = 0; 

int main(object me, string arg)	//ֻ�ǳ��Σ����Լ���call_out�����Զ���������÷���natured.c ���档
{                       //�׳�canoe,����natured.c���滹��������npc����������Զ�����,cs����ϵͳ�Ѿ�ȫ�����.(takeע)
	int i,j,k ;
	string cStatus,tStatus,name,faction ;
	object *oUser,*tUser,ob,*Ffire,fire,*inv ;
	oUser = users();
	tUser = users();
		
	if( !arg ) 
	{
		if ( !PK_Start )
			write("�� CS ��������û�п�ʼ��\n");
		else
		{
			if (wizardp(me)) 
			{
				cStatus = chinese_number ( TWin );
				write(HIW"\n�� CS ������"+HIR"�ݻ�"+HIW"���Ѿ����"HIY+ cStatus +HIW"��ʤ����\n"NOR);
				cStatus = chinese_number ( CtWin );
				write(HIW"\n�� CS ������"+HIG"����"+HIW"���Ѿ����"HIY+ cStatus +HIW"��ʤ����\n"NOR);
				write(HIW"\n�� CS ���������ֱ���"+HIR"�ݻ�"+HIW"�黹ʣ��:\n\n"NOR);
				for ( i = 0 ; i < sizeof(oUser) ; i ++ ) 
	                	{
        	        		if( (oUser[i]->query_temp("pkgame")=="t") && (environment(oUser[i])->query("short") != HIR"CS��Ϣ��"NOR) )
                		        {
                		        	cStatus = HIR""+oUser[i]->query("name")+" ("+oUser[i]->query("id")+")"NOR ;
                				inv = all_inventory(oUser[i]);
                                        	for(j=0; j<sizeof(inv); j++) 
                                        	{
                                        		if( inv[j]->query("bomb") )
                                        			cStatus = BRED HIY""+oUser[i]->query("name")+" ("+oUser[i]->query("id")+")"NOR ;
                                        	}
                                        	write (cStatus+"	");
                                        }
	         		}
                		write(HIW"\n\n�� CS ���������ֱ���"+HIG"����"+HIW"�黹ʣ��:\n\n"NOR);
                		for ( i = 0 ; i < sizeof(oUser) ; i ++ ) 
	                	{
        	        		if( (oUser[i]->query_temp("pkgame")=="ct") && (environment(oUser[i])->query("short") != HIR"CS��Ϣ��"NOR) )
                				write(HIG""+oUser[i]->query("name")+" ("+oUser[i]->query("id")+")	"NOR);
                		}
                		cStatus = chinese_number ( 7 - ( time() - this_object()->query("PkTime") )/ 60  ) ;
				write(HIW"\n\n\n�� CS ���������ֻ�ʣ"BLINK HIY+cStatus+NOR""+HIW"���ӡ�\n\n"NOR);
				return 1;
			}
			
			if (me->query_temp("pkgame") == "t") 
			{
				cStatus = chinese_number ( TWin );
				write(HIW"\n�� CS ���������С���Ѿ����"HIG+ cStatus +HIW"��ʤ����\n"NOR);
				cStatus = chinese_number ( CtWin );
				write(HIW"\n�� CS �������Է�С���Ѿ����"HIR+ cStatus +HIW"��ʤ����\n"NOR);
				write(HIW"\n�� CS ���������ֱ������С�黹ʣ��:\n\n"NOR);
				for ( i = 0 ; i < sizeof(oUser) ; i ++ ) 
	                	{
        	        		if( (oUser[i]->query_temp("pkgame")=="t") && (environment(oUser[i])->query("short") != HIR"CS��Ϣ��"NOR) )
                		        {
                		        	cStatus = HIG""+oUser[i]->query("name")+" ("+oUser[i]->query("id")+")"NOR ;
                				inv = all_inventory(oUser[i]);
                                        	for(j=0; j<sizeof(inv); j++) 
                                        	{
                                        		if( inv[j]->query("bomb") )
                                        			cStatus = BRED HIG""+oUser[i]->query("name")+" ("+oUser[i]->query("id")+")"NOR ;
                                        	}
                                        	write (cStatus+"	");
                                        }
	         		}
                		write(HIW"\n\n�� CS ���������ֱ����Է�С�黹ʣ��:\n\n"NOR);
                		for ( i = 0 ; i < sizeof(oUser) ; i ++ ) 
	                	{
        	        		if( (oUser[i]->query_temp("pkgame")=="ct") && (environment(oUser[i])->query("short") != HIR"CS��Ϣ��"NOR) )
                				write(HIR""+oUser[i]->query("name")+" ("+oUser[i]->query("id")+")	"NOR);
                		}   	        	
			}
			
			if (me->query_temp("pkgame") == "ct") 	
			{
				cStatus = chinese_number ( CtWin );
				write(HIW"\n�� CS ���������С���Ѿ����"HIG+ cStatus +HIW"��ʤ����\n"NOR);
				cStatus = chinese_number ( TWin );
				write(HIW"\n�� CS �������Է�С���Ѿ����"HIR+ cStatus +HIW"��ʤ����\n"NOR);
				write(HIW"\n�� CS ���������ֱ������С�黹ʣ��:\n\n"NOR);
				for ( i = 0 ; i < sizeof(oUser) ; i ++ ) 
	                	{
        	        		if( (oUser[i]->query_temp("pkgame")=="ct") && (environment(oUser[i])->query("short") != HIR"CS��Ϣ��"NOR) )
                				write(HIG""+oUser[i]->query("name")+" ("+oUser[i]->query("id")+")	"NOR);
                		}
                		write(HIW"\n\n�� CS ���������ֱ����Է�С�黹ʣ��:\n\n"NOR);
                		for ( i = 0 ; i < sizeof(oUser) ; i ++ ) 
	                	{
        	        		if( (oUser[i]->query_temp("pkgame")=="t") && (environment(oUser[i])->query("short") != HIR"CS��Ϣ��"NOR) )
                				write(HIR""+oUser[i]->query("name")+" ("+oUser[i]->query("id")+")	"NOR);
                		}   	        
                	}		
	     	cStatus = chinese_number ( 7 - ( time() - this_object()->query("PkTime") )/ 60  ) ;
		write(HIW"\n\n\n�� CS ���������ֻ�ʣ"BLINK HIY+cStatus+NOR""+HIW"���ӡ�\n\n"NOR);
		}
		return 1 ;
	}	
	if ( me )
	{
		cStatus = SECURITY_D->get_status(me);
		if( cStatus != "(admin)" && cStatus != "(arch)" )
		return notify_fail("ֻ�� (arch) ���ϵ���ʦ�������� CS ���� ��\n");
		if( sscanf(arg, "%s %s", name, faction)==2 )
		{
			ob = find_player(name);
                	if ( !ob ) return notify_fail("�Ҳ��������ҡ�\n");
                	if ( faction != "ct" && faction != "t")
                		return notify_fail("��ֻ��ָ�����Ϊ [ t ] ���� [ ct ]\n");
                	if ( ob->query_temp("in_hell") )
                		return notify_fail("��λ����Ѿ������ǣ����ܲμӱ�����\n");
               		if ( faction == "t")
               		{
               			ob->set_temp("pkgame","t");
               			faction = "�ݻ�";
               		}
               		if ( faction == "ct")
               		{
               			ob->set_temp("pkgame","ct");
               			faction = "����";
               		}
               		message( "system", HIR"�� CS �������� "+ob->query("family/family_name")+HIY""+ob->query("name")+HIR"����"HIY+faction+HIR"�顣\n" NOR, users() );
               		return 1;
        	}
		if ( arg != "start" && arg != "over" )
			return notify_fail("ָ���ʽ��PkGame [ start | over ]\n");
	}
	if ( arg =="start" )
	{
		if ( (me) && (PK_Start) )
			return notify_fail(" CS �����Ѿ�������\n");
		PK_Start = 1 ;
		this_object()->set( "PkTime" , time() );
		tUser = users();
		j=0;
		k=0;
		for ( i = 0 ; i < sizeof(oUser) ; i ++ ) 	
        	{
	       		if (oUser[i]->query_temp("pkgame")=="t")
        		{
        			oUser[i]->move("/d/kaifeng/tieta");
        			oUser[i]->delete_temp("last_damage_from");
        			oUser[i]->delete_temp("my_killer");
        			oUser[i]->delete_temp("last_opponent");
        		 	tUser[j]=oUser[i];
	       			j++;
        		}
        		if (oUser[i]->query_temp("pkgame")=="ct") 
        		{
        			oUser[i]->move("/d/qujing/lingshan/siqian");
        			oUser[i]->delete_temp("last_damage_from");
        			oUser[i]->delete_temp("my_killer");
        			oUser[i]->delete_temp("last_opponent");
        			k++;
        		}
        	}
   		if ( !j && !k )
   		{
   			sort();
   			return 1;
   		}   			
   		if ( !j ) 
   		{
   			CtWin=5;
			message( "system", BLINK HIR"\n\n�� CS �������� �����ݻ���ȫ���Ա�������⣬����������\n\n" NOR, users() );
   			call_out("sort",1);
   			return 1;
   		}
   		if ( !k ) 
   		{
   			TWin=5;
			message( "system", BLINK HIR"\n\n�� CS �������� ���ڴ�����ȫ���Ա�������⣬����������\n\n" NOR, users() );
   			call_out("sort",1);
   			return 1;
   		}
   		message( "chat", HIY"\n\n��̫ƽʢ����˳���(Shunfeng er)����˵ǰ����һ�����͵�߻������Ļ������֪ȥ�򡣡���������\n\n"NOR, users() );
		for ( i = 0 ; i < sizeof(oUser) ; i ++ ) 
        	{
              oUser[i]->set_temp("block_msg/all", 0);
        		oUser[i]->delete_temp("firewait");
        		oUser[i]->delete_temp("waitwin");
        	}
		j = random(j);
		Ffire = children ("/d/dntg/sky/obj/huolingfu");
		for ( i = 0 ; i < sizeof(Ffire) ; i ++ )
		{
			destruct( Ffire[i] );
	        }
	        Ffire = children ("/d/dntg/sky/obj/fire");
		for ( i = 0 ; i < sizeof(Ffire) ; i ++ )
		{
			destruct( Ffire[i] );
	        }      
		fire = new("/d/dntg/sky/obj/huolingfu");
		fire->move(tUser[j]);
	     	message_vision (HIR"\n\n�������$N���ϳ��֣����ڿ�ʼ�ж���\n"NOR, tUser[j]);
		call_out("check_player",5);
		call_out( "ToOver" ,60*7 );
	}
	else
	{
		if ( (me) && (!PK_Start) )
			return notify_fail(" �ã� ������û����������ô�ܹرգ�\n");
		sort();
	}
	return 1;
}

void ToOver()
{
	remove_call_out("ToOver");
        CtWin++;
        if ( CtWin >= 5 )
        	{
        		sort();
        		return;
        	}
	message( "system", BLINK HIR"\n�� CS �������� ���ֽ������˾ֱ���"+HIY"����"+BLINK HIR"���ʤ,���λ׼��5���Ӻ�ʼ��һ�ֱ���������������\n" NOR, users() );
	call_out("over" , 1);
}

void sort()
{
	object *oUser,*Ffire,winner;
	string faction;
 	mapping skill;
	int i,present_exp,present_daoxing,present_potential,wintimes;
	wintimes = 0;
	remove_call_out("over");
	remove_call_out("ToOver");
	remove_call_out("main");
	if ( CtWin >= 5 ) faction = "����";
	if ( TWin >= 5 ) faction = "�ݻ�";
	if ( (CtWin >= 5) || (TWin >= 5) )
	message( "system", BLINK HIR"\n\n�� CS �������� ������������"+HIY""+ faction +BLINK HIR"�����ܹھ���\n\n" NOR, users() );
	else
	message( "system", BLINK HIR"\n\n�� CS �������� ��������������ԭ������ֹ��\n\n" NOR, users() );
	oUser = users();
	for ( i = 0 ; i < sizeof(oUser) ; i ++ ) 
        {
        	if (oUser[i]->query_temp("pkgame"))
        	{
        		oUser[i]->move("/d/city/kezhan");
                         if ( ((CtWin >= 5) && (oUser[i]->query_temp("pkgame")=="ct")) || ((TWin >= 5) && (oUser[i]->query_temp("pkgame")=="t")) )
        		{
        			present_exp = present_users(oUser[i]);
        			present_daoxing = present_users(oUser[i]);
        			present_potential = present_users(oUser[i]);
        			oUser[i]->add("combat_exp",present_exp);
        			oUser[i]->add("potential",present_potential);
        			oUser[i]->add("daoxing",present_daoxing);
							message( "chat", HIC"��"+HIY"��������"+HIC"���� "HIC+oUser[i]->query("family/family_name")+HIY""+oUser[i]->query("name")+HIC"��ããӴ�����������ѧ"+chinese_number (present_exp)+"�㣬����"+chinese_number (present_daoxing/1000)+"�꣬Ǳ��"+chinese_number (present_potential)+"�㡣\n" NOR, users() );
	       		  if ( wintimes < oUser[i]->query_temp("pgwin") )
	       		  {
	       		  	winner = oUser[i];
	       		  	wintimes = oUser[i]->query_temp("pgwin");
	       		  }
	       		}
        		oUser[i]->set("eff_kee",oUser[i]->query("max_kee"));
         		oUser[i]->set("eff_sen",oUser[i]->query("max_sen"));
          	oUser[i]->set("kee",oUser[i]->query("max_kee"));
          	oUser[i]->set("sen",oUser[i]->query("max_sen"));
          	oUser[i]->set("force",oUser[i]->query("max_force"));
          	oUser[i]->set("mana",oUser[i]->query("max_mana"));
        		oUser[i]->delete_temp("firewait");
        		oUser[i]->delete_temp("waitwin");
        		oUser[i]->delete_temp("pkgame");
        		oUser[i]->delete_temp("PkTime");
        		oUser[i]->delete_temp("pgwin");
        		oUser[i]->delete_temp("last_damage_from");
                 oUser[i]->delete("PKS");
        		oUser[i]->delete_temp("my_killer");
        		oUser[i]->delete_temp("last_opponent");
        	}
        }
  
  if ( winner ) 
  {
  	skill=keys(winner->query_skills())[random(sizeof(keys(winner->query_skills())))];
		winner->set_skill(skill,winner->query_skills()[skill]+1);
		message( "chat", HIC"\n\n��"+HIY"��������"+HIC"������ϲ "HIC+winner->query("family/family_name")+HIY""+winner->query("name")+HIC"��ããӴ���������"BLINK HIY+to_chinese(skill)+NOR""+HIC"һ����\n" NOR, users() );
	}
  Ffire = children ("/d/dntg/sky/obj/huolingfu");
	for ( i = 0 ; i < sizeof(Ffire) ; i ++ )
	{
		destruct( Ffire[i] );
	}
	Ffire = children ("/d/dntg/sky/obj/fire");
	for ( i = 0 ; i < sizeof(Ffire) ; i ++ )
	{
		destruct( Ffire[i] );
        }      
        CtWin = 0 ;
        TWin = 0 ;
        PK_Start = 0 ;
        children("/u/take/cs")->set( "End_Time" , time() );
        "/u/take/cs"->end_game();
        return;
}

void over()
{
	remove_call_out("over");
	remove_call_out("ToOver");
	remove_call_out("main");
	call_out("main" , 5 , 0, "start");
}

int query_pk()
{
	return PK_Start ;
}

void query_Win(string arg)
{
	object *oUser;
	int i;
	if ( !arg ) return;
	oUser = users();
	for ( i = 0 ; i < sizeof(oUser) ; i ++ ) 
        {
        	if ( (oUser[i]->query_temp("pkgame")) && (environment(oUser[i])->query("short") != HIR"CS��Ϣ��"NOR) )
        		{
	       			oUser[i]->set_temp("block_msg/all", 1);
        			oUser[i]->move("/u/take/waitpk");
        			oUser[i]->set_temp("block_msg/all", 0);
        		}
        }
        if ( arg == "t" )
        TWin++;
        else
        CtWin++;
        if ( (CtWin >= 5) || (TWin >= 5) )
        call_out("sort",2);
}

int present_users(object me)
{
	int present = 0;
	if (!me) return 0;
	present = (me->query_temp("pgwin")*300+random(me->query_temp("pgwin")*300));
	return present;
}
	
void check_player()
{
        object *oUser ;
        int i ;
        if ( !"/cmds/usr/pkgame"->query_pk() ) return;
        remove_call_out("check_player");
        oUser = users();
        for ( i = 0 ; i < sizeof(oUser) ; i ++ ) 
        {
        	if ( (oUser[i]->query_temp("pkgame")) && (environment(oUser[i])->query("no_fight")) && (environment(oUser[i])->query("short") != HIR"CS��Ϣ��"NOR) && (!wizardp(oUser[i])) )
        	{
        		oUser[i]->add("eff_kee",-oUser[i]->query("max_kee")/10);
                	oUser[i]->add("eff_sen",-oUser[i]->query("max_sen")/10);
                	oUser[i]->add("kee",-oUser[i]->query("max_kee")/10);
                	oUser[i]->add("sen",-oUser[i]->query("max_sen")/10);
                	oUser[i]->add("force",-oUser[i]->query("max_force")/10);
                	oUser[i]->add("mana",-oUser[i]->query("max_mana")/10);
                	oUser[i]->set_temp("last_damage_from",oUser[i]);
			message( "tell", HIW"�� CS ���������������ڱ����ڼ���ڰ�ȫ������ľ�����Ѫ�������ͷ����������½����㻹�Ǿ����뿪��ȫ���ɣ�\n\n" NOR, oUser[i] );
		}
	}
	call_out("check_player",5);
}

int help(object me)
{
  write(@HELP
ָ���ʽ : PkGame [ start | over ]

���ô�һָ��ɲ쿴�������͹ر� CS ������
HELP
    );
    return 1;
}
