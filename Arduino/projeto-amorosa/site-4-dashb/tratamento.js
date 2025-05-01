class TemperatureDashboard {
    constructor(chartId, displayId, listId, csvFilePath) {
        this.chartId = chartId;
        this.displayId = displayId;
        this.listId = listId;
        this.csvFilePath = csvFilePath;
        this.temperatureChart = null;
        this.initChart();
        this.loadCSV();
    }

    initChart() {
        const ctx = document.getElementById(this.chartId).getContext('2d');
        this.temperatureChart = new Chart(ctx, {
            type: 'line',
            data: {
                labels: [],
                datasets: [{
                    label: 'Temperatura (°C)',
                    data: [],
                    borderColor: 'rgba(75, 192, 192, 1)',
                    borderWidth: 2,
                    fill: false
                }]
            },
            options: {
                responsive: true,
                scales: {
                    x: {
                        type: 'time',
                        time: {
                            unit: 'minute',
                            tooltipFormat: 'Pp'
                        },
                        title: {
                            display: true,
                            // text: 'Hora'
                        }
                    },
                    y: {
                        title: {
                            display: true,
                            // text: 'Temperatura (°C)'
                        }
                    }
                }
            }
        });
    }

    loadCSV() {
        this.fetchCSV(this.csvFilePath);
    }

    fetchCSV(csvFilePath) {
        fetch(csvFilePath)
            .then(response => response.text())
            .then(text => {
                this.processCSV(text);
            })
            .catch(error => {
                console.error('Error fetching the CSV file:', error);
            });
    }

    processCSV(text) {
        const lines = text.split('\n');
        const data = lines.map(line => {
            const parts = line.split(',');
            if (parts.length >= 2) {
                const temperature = parseFloat(parts[0].trim());
                const timestamp = parts[1].trim();
                return { temperature, timestamp };
            }
            return null;
        }).filter(item => item !== null);
    
        if (data.length > 0) {
            this.updateTemperatureList(data);
            this.updateChart(data);
        } else {
            document.getElementById(this.displayId).innerText = 'No valid data';
        }
    }

    updateTemperatureList(data) {
        const temperatureList = document.getElementById(this.listId);
        temperatureList.innerHTML = '';
        data.forEach(item => {
            const listItem = document.createElement('li');
            listItem.textContent = `Temperatura - ${item.temperature} °C  Data - ${item.timestamp}`;
            temperatureList.appendChild(listItem);
        });

        const latestData = data[data.length - 1];
        document.getElementById(this.displayId).innerText = `Ultima Temperatura ${latestData.temperature} °C - ${latestData.timestamp}`;
        
    }

    updateChart(data) {
        this.temperatureChart.data.labels = data.map(item => new Date(item.timestamp));
        this.temperatureChart.data.datasets[0].data = data.map(item => item.temperature);
        this.temperatureChart.update();
    }
}

document.addEventListener('DOMContentLoaded', () => {
    new TemperatureDashboard('temperatureChart1', 'temperatureDisplay1', 'temperatureList', 'temperatura_data.csv');
    new TemperatureDashboard('temperatureChart2', 'temperatureDisplay2', 'temperatureList', 'temperatura_data2.csv');
    new TemperatureDashboard('temperatureChart3', 'temperatureDisplay3', 'temperatureList', 'temperatura_data3.csv');
    new TemperatureDashboard('temperatureChart4', 'temperatureDisplay4', 'temperatureList', 'temperatura_data4.csv');
});
