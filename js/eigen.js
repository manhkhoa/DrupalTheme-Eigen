/**
 * @file
 * A JavaScript file for the theme.
 *
 * In order for this JavaScript to be loaded on pages, see the instructions in
 * the README.txt next to this file.
 */

// JavaScript should be made compatible with libraries other than jQuery by
// wrapping it with an "anonymous closure". See:
// - http://drupal.org/node/1446420
// - http://www.adequatelygood.com/2010/3/JavaScript-Module-Pattern-In-Depth
(function ($, Drupal, window, document, undefined) {
// Place your code here.
$(window).load(function(){
	$(document).ready(function() {
		$('.superfish ul.menu').superfish({
				delay:       100,
				animation:   {opacity:'show',height:'show'},
				speed:       500,
				autoArrows:  true,
				dropShadows: true
		});
		// Add equal heihgt for Content , sidebar for devices has width >= 1024px . Ex:
		if(window.innerWidth >= 960){
			 $(".column").equalHeight();
		}
		else if(window.innerWidth >= 600){
			$(".column").css("min-height","auto");
		  	$(".sidebar").equalHeight();
		}
		else {
			$(".column").css("min-height","auto");
		}
		$(window).resize(function() {
			if(window.innerWidth >= 960){
				 $(".column").equalHeight();
			}
			else if(window.innerWidth >= 600){
			  $(".column").css("min-height","auto");
			  $(".sidebar").equalHeight();
			}
			else {
				$(".column").css("min-height","auto");
			}
		});
		// Add javascript to search box
		$('#search-block-form .form-text').attr('value',Drupal.t('Search this page...'));
		$('#search-block-form .form-text').focus(
			function(){
				if($(this).attr('value') == Drupal.t('Search this page...'))
					$(this).attr('value','');
			});
		$('#search-block-form .form-text').blur(
			function(){
				if($(this).attr('value') == "")
					$(this).attr('value',Drupal.t('Search this page...'));
		});
		// Add javascript to Email box
		$('#block-block-34 .form-text').attr('value',Drupal.t('Email'));
		$('#block-block-34 .form-text').focus(
			function(){
				if($(this).attr('value') == Drupal.t('Email'))
					$(this).attr('value','');
			});
		$('#block-block-34 .form-text').blur(
			function(){
				if($(this).attr('value') == "")
					$(this).attr('value',Drupal.t('Email'));
		});
	});
});
})(jQuery, Drupal, this, this.document);
