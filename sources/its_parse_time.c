/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   its_parse_time.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 16:43:26 by fjanoty           #+#    #+#             */
/*   Updated: 2016/09/09 16:52:56 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 *	On lis ligne par ligne
 *	On split sur les '\n' 
 *	On va changer tout les ['	', '\r', '\t'] etc en espace : ' '
 *	On split sur les espace eventuelement
 *	
 *	On connait les dimmantion de la map
 *	On malloc la map a la bonne taille 
 *	
 *	On fait le atoi modifier pour aussi choper les couleur de le map
 * */
