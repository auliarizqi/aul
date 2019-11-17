//Declare suhu

const Firebase = firebase.database().ref().child("Monitoring");
const newFireBase = Firebase.child("Temp");
var result;
var snap = function(datasnapshot){
	result = parseFloat(datasnapshot.val())
};
newFireBase.on("value",snap)
Highcharts.setOptions({
	global: {
		useUTC: false
	}
})

//Declare kelembaban

const Firebase2 = firebase.database().ref().child("Monitoring");
const newFireBase2 = Firebase2.child("Humidity");
var result2;
var snap = function(datasnapshot){
	result2 = parseFloat(datasnapshot.val())
};
newFireBase2.on("value",snap)
Highcharts.setOptions({
	global: {
		useUTC: false
	}
});

//Chart
Highcharts.stockChart('content',{
	chart: {
		events: {
			load: function(){

				//set up the updating of the chart each second

				var series = this.series[0];
				var series1 = this.series[1];
				setInterval(function(){
					var x = (new Date()).getTime(), //current time
						y = result,
						z = result2;
						console.log(x);
						series.addPoint([x, y], true);
						series1.addPoint([x, z], true);
				}, 1000);
			}
		}
	},

rangeSelector: {
	buttons: [{
		count: 1,
		type: 'minute',
		text: '1M'
},{
	count: 5,
	type: 'minute',
	text: '1M'
},{
	type: 'all',
	text: 'All'
}],
inputEnabled: false,
selected: 0
},

title: {
	text: 'Suhu dan Kelembaban DHT-11 versi Highstock'
},

tooltip: {
	split: true
},

yAxis: {
	title: {
		text:'Suhu \xB0'
	}
},

exporting: {
	enabled: false
},

series: [{
	name: 'Suhu',
	data: [[new Date().getTime().result]]
	//to show number of temperature from firebase
},
{
	name: 'Kelembaban',
	data: [[new Date().getTime().result2]]
	//to show number of humidity from firebase
}]
});